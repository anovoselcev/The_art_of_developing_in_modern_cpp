#include "../../TestRunner/test_runner.h"

#include <numeric>
#include <vector>
#include <string>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <mutex>
using namespace std;

template <typename T>
class Synchronized {
public:
  explicit Synchronized(T initial = T())
    : value(move(initial))
  {
  }

  struct Access {
    T& ref_to_value;
    lock_guard<mutex> guard;
  };

  Access GetAccess() {
    return {value, lock_guard(m)};
  }

private:
  T value;
  mutex m;
};

void TestConcurrentUpdate() {
  Synchronized<string> common_string;

  const size_t add_count = 50000;
  auto updater = [&common_string, add_count] {
    for (size_t i = 0; i < add_count; ++i) {
      auto access = common_string.GetAccess();
      access.ref_to_value += 'a';
    }
  };

  auto f1 = async(updater);
  auto f2 = async(updater);

  f1.get();
  f2.get();

  ASSERT_EQUAL(common_string.GetAccess().ref_to_value.size(), 2 * add_count);
}

vector<int> Consume(Synchronized<deque<int>>& common_queue) {
  vector<int> got;

  for (;;) {
    deque<int> q;

    {
      // РњС‹ СЃРїРµС†РёР°Р»СЊРЅРѕ Р·Р°РєР»СЋС‡РёР»Рё СЌС‚Рё РґРІРµ СЃС‚СЂРѕС‡РєРё РІ РѕРїРµСЂР°С‚РѕСЂРЅС‹Рµ СЃРєРѕР±РєРё, С‡С‚РѕР±С‹
      // СѓРјРµРЅСЊС€РёС‚СЊ СЂР°Р·РјРµСЂ РєСЂРёС‚РёС‡РµСЃРєРѕР№ СЃРµРєС†РёРё. РџРѕС‚РѕРє-РїРѕС‚СЂРµР±РёС‚РµР»СЊ Р·Р°С…РІР°С‚С‹РІР°РµС‚
      // РјСЊСЋС‚РµРєСЃ, РїРµСЂРµРјРµС‰Р°РµС‚ РІСЃС‘ СЃРѕРґРµСЂР¶РёРјРѕРµ РѕР±С‰РµР№ РѕС‡РµСЂРµРґРё РІ СЃРІРѕСЋ
      // Р»РѕРєР°Р»СЊРЅСѓСЋ РїРµСЂРµРјРµРЅРЅСѓСЋ Рё РѕС‚РїСѓСЃРєР°РµС‚ РјСЊСЋС‚РµРєСЃ. РџРѕСЃР»Рµ СЌС‚РѕРіРѕ РѕРЅ РѕР±СЂР°Р±Р°С‚С‹РІР°РµС‚
      // РѕР±СЉРµРєС‚С‹ РІ РѕС‡РµСЂРµРґРё Р·Р° РїСЂРµРґРµР»Р°РјРё РєСЂРёС‚РёС‡РµСЃРєРѕР№ СЃРµРєС†РёРё, РїРѕР·РІРѕР»СЏСЏ
      // РїРѕС‚РѕРєСѓ-РїСЂРѕРёР·РІРѕРґРёС‚РµР»СЋ РїР°СЂР°Р»Р»РµР»СЊРЅРѕ РїРѕРјРµС‰Р°С‚СЊ РІ РѕС‡РµСЂРµРґСЊ РЅРѕРІС‹Рµ РѕР±СЉРµРєС‚С‹.
      //
      // Р Р°Р·РјРµСЂ РєСЂРёС‚РёС‡РµСЃРєРѕР№ СЃРµРєС†РёРё СЃСѓС‰РµСЃС‚РІРµРЅРЅРѕ РІР»РёСЏРµС‚ РЅР° Р±С‹СЃС‚СЂРѕРґРµР№СЃС‚РІРёРµ
      // РјРЅРѕРіРѕРїРѕС‚РѕС‡РЅС‹С… РїСЂРѕРіСЂР°РјРј.
      auto access = common_queue.GetAccess();
      q = move(access.ref_to_value);
    }

    for (int item : q) {
      if (item > 0) {
        got.push_back(item);
      } else {
        return got;
      }
    }
  }
}

void TestProducerConsumer() {
  Synchronized<deque<int>> common_queue;

  auto consumer = async(Consume, ref(common_queue));

  const size_t item_count = 100000;
  for (size_t i = 1; i <= item_count; ++i) {
    common_queue.GetAccess().ref_to_value.push_back(i);
  }
  common_queue.GetAccess().ref_to_value.push_back(-1);

  vector<int> expected(item_count);
  iota(begin(expected), end(expected), 1);
  ASSERT_EQUAL(consumer.get(), expected);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestConcurrentUpdate);
  RUN_TEST(tr, TestProducerConsumer);
}
