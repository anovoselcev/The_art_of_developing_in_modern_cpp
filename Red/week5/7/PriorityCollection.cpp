
#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>
#include <map>
#include<set>
using namespace std;
template <typename T>
class PriorityCollection {
public:

    PriorityCollection() {
        objects.reserve(1'000'000);
    }

    using Id = int;
    using IT = set<pair<int, Id>>::iterator;

    Id Add(T object) {
        objects.push_back({ move(object), priorities.end()});
        IT it = (priorities.insert({ 0, id })).first;
        objects.back().second = it;
        return id++;
    }

    template <typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin, ObjInputIt range_end,
        IdOutputIt ids_begin) {
        for (auto it = make_move_iterator(range_begin);
            it != make_move_iterator(range_end); ++it) {
            *(ids_begin++) = Add(*it);
        }
    }

    bool IsValid(Id id) const {
        if (id > objects.size() - 1) {
            return false;
        }
        return objects[id].second != priorities.end();
    }

    const T& Get(Id id) const {
        return objects[id].first;
    }

    void Promote(Id id) {
//        auto tmp = GetPriority(id);
//        priorities.erase(tmp);
//        tmp.first++;
//        objects[id].second;
//        priorities.insert({(tmp.first), tmp.second});
       IT it_old = objects[id].second;
       int tmp_priority = (*it_old).first;
       priorities.erase(it_old);
       IT it_new = (priorities.insert({ ++tmp_priority, id })).first;
       objects[id].second = it_new;
    }

    pair<const T&, int> GetMax() const {
        auto max_it = prev(priorities.end());
        return { objects[max_it->second].first, max_it->first};
    }

    pair<T, int> PopMax() {
        auto it = prev(priorities.end());
        int priority = it->first;
        Id max_id = it->second;
        priorities.erase(it);
        objects[max_id].second = priorities.end();
        return { move(objects[max_id].first), priority};
    }

private:
    Id id = 0;
    set<pair<int, Id>> priorities;
    vector<pair<T, IT>> objects;

    pair<int, Id> GetPriority(Id id) {
    	return {objects[id].second, id};
    }
};

class StringNonCopyable : public string {
public:
  using string::string;  // РџРѕР·РІРѕР»СЏРµС‚ РёСЃРїРѕР»СЊР·РѕРІР°С‚СЊ РєРѕРЅСЃС‚СЂСѓРєС‚РѕСЂС‹ СЃС‚СЂРѕРєРё
  StringNonCopyable(const StringNonCopyable&) = delete;
  StringNonCopyable(StringNonCopyable&&) = default;
  StringNonCopyable& operator=(const StringNonCopyable&) = delete;
  StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
  PriorityCollection<StringNonCopyable> strings;
  const auto white_id = strings.Add("white");
  const auto yellow_id = strings.Add("yellow");
  const auto red_id = strings.Add("red");

  strings.Promote(yellow_id);
  for (int i = 0; i < 2; ++i) {
    strings.Promote(red_id);
  }
  strings.Promote(yellow_id);
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "red");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "yellow");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "white");
    ASSERT_EQUAL(item.second, 0);
  }
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestNoCopy);
  return 0;
}
