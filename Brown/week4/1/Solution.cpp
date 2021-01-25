#include "Common.h"
#include <mutex>
#include <algorithm>
#include <unordered_map>
using namespace std;
class LruCache : public ICache {
public:
    LruCache(
        shared_ptr<IBooksUnpacker> books_unpacker,
        const Settings& settings
    ) : _unpack(books_unpacker),
        _max_size(settings){}

    BookPtr GetBook(const string& book_name) override {
        std::lock_guard<std::mutex> guard(_mutex);
        if (_cache[book_name]._ptr == nullptr) {
            auto tmp_ptr = _unpack->UnpackBook(book_name);
            if (tmp_ptr->GetContent().size() > _max_size.max_memory) {
                _cache.clear();
                _curr_size.max_memory = 0;
                _max_priority = 1;
                return tmp_ptr;
            }
            _cache[book_name]._ptr = std::move(tmp_ptr);
            _cache[book_name]._priority = ++_max_priority;
            if (_max_priority == ULLONG_MAX)
                DecreasePriority(book_name);
            ClearCache(_cache[book_name]._ptr->GetContent().size());
            _curr_size.max_memory += _cache[book_name]._ptr->GetContent().size();
        }
        else _cache[book_name]._priority = ++_max_priority;

        return _cache[book_name]._ptr;
    }
private:

    void DecreasePriority(const string& name) {
        for (auto& [_, value] : _cache)
            value._priority /= 100000;
        _cache[name]._priority++;
        _max_priority = _cache[name]._priority;
    }

    void ClearCache(size_t upd) {
        while (_curr_size.max_memory + upd > _max_size.max_memory) {
            auto element = std::min_element(_cache.begin(), _cache.end(),
                [](const auto& lhs, const auto& rhs) {
                    return lhs.second._priority < rhs.second._priority; });
            if (element->second._ptr) {
                _curr_size.max_memory -= element->second._ptr->GetContent().size();
                _cache.erase(element);
            }
        }
    }

    struct BookPriority {
        BookPtr _ptr;
        size_t _priority = 0;
    };


    shared_ptr<IBooksUnpacker> _unpack;
    std::unordered_map < string, BookPriority>_cache;
    ICache::Settings _max_size;
    ICache::Settings _curr_size = {0};
    size_t _max_priority = 1;
    std::mutex _mutex;
};


unique_ptr<ICache> MakeCache(
    shared_ptr<IBooksUnpacker> books_unpacker,
    const ICache::Settings& settings
) {
    return std::make_unique<LruCache>(books_unpacker, settings);
}
