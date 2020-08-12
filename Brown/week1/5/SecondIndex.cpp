#include "../../TestRunner/test_runner.h"

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>

using namespace std;

struct Record {
    string id;
    string title;
    string user;
    int timestamp;
    int karma;
};

struct Data {
    Record ptr;
    multimap<int, const Record*>::iterator first;
    multimap<string, const Record*>::iterator second;
    multimap<int, const Record*>::iterator third;
};

class Database {
public:
    bool Put(const Record& record) {
        auto [it, isSuccess] = id_s.insert({record.id, Data{record, {}, {}, {}}});
        if (!isSuccess) {
            return false;
        }
        auto& data = it->second;
        const Record* ptr = &data.ptr;
        data.first = timestamps.insert({record.timestamp, ptr});
        data.second = users.insert({record.user, ptr});
        data.third = karmas.insert({record.karma, ptr});
        return true;
    }

    const Record* GetById(const string& id) const {
        auto it = id_s.find(id);
        return it == id_s.end() ? nullptr : &it->second.ptr;
    }

    bool Erase(const string& id) {
        auto it = id_s.find(id);
        if (it == id_s.end()) {
            return false;
        }
        const auto& data = it->second;
        timestamps.erase(data.first);
        users.erase(data.second);
        karmas.erase(data.third);
        id_s.erase(it);
        return true;
    }

    template <typename Callback>
    void RangeByTimestamp(int low, int high, Callback callback) const {
        if (low > high) {
            return;
        }
        auto it_begin = timestamps.lower_bound(low);
        auto it_end = timestamps.upper_bound(high);
        for (auto it = it_begin; it != it_end; ++it) {
            if (!callback(*it->second)) {
                break;
            }
        }
    }

    template <typename Callback>
    void RangeByKarma(int low, int high, Callback callback) const {
        if (low > high) {
            return;
        }
        auto it_begin = karmas.lower_bound(low);
        auto it_end = karmas.upper_bound(high);
        for (auto it = it_begin; it != it_end; ++it) {
            if (!callback(*it->second)) {
                break;
            }
        }
    }

    template <typename Callback>
    void AllByUser(const string& user, Callback callback) const {
        auto [it, end] = users.equal_range(user);
        while (it != end && callback(*it->second)) {
            ++it;
        }
    }

private:
    template<typename Type>
    using Index = multimap<Type, const Record*>;

    unordered_map<string, Data> id_s;
    Index<int> timestamps;
    Index<string> users;
    Index<int> karmas;
};
void TestRangeBoundaries() {
  const int good_karma = 1000;
  const int bad_karma = -10;

  Database db;
  db.Put({"id1", "Hello there", "master", 1536107260, good_karma});
  db.Put({"id2", "O>>-<", "general2", 1536107260, bad_karma});

  int count = 0;
  db.RangeByKarma(bad_karma, good_karma, [&count](const Record&) {
    ++count;
    return true;
  });

  ASSERT_EQUAL(2, count);
}

void TestSameUser() {
  Database db;
  db.Put({"id1", "Don't sell", "master", 1536107260, 1000});
  db.Put({"id2", "Rethink life", "master", 1536107260, 2000});

  int count = 0;
  db.AllByUser("master", [&count](const Record&) {
    ++count;
    return true;
  });

  ASSERT_EQUAL(2, count);
}

void TestReplacement() {
  const string final_body = "Feeling sad";

  Database db;
  db.Put({"id", "Have a hand", "not-master", 1536107260, 10});
  db.Erase("id");
  db.Put({"id", final_body, "not-master", 1536107260, -10});

  auto record = db.GetById("id");
  ASSERT(record != nullptr);
  ASSERT_EQUAL(final_body, record->title);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestRangeBoundaries);
  RUN_TEST(tr, TestSameUser);
  RUN_TEST(tr, TestReplacement);
  return 0;
}
