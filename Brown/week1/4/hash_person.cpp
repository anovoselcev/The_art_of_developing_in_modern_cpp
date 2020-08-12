#include "../../TestRunner/test_runner.h"
#include <limits>
#include <random>
#include <unordered_set>

using namespace std;

struct Address {
  string city, street;
  int building;

  bool operator==(const Address& other) const {
	  return city == other.city && street == other.street && building == other.building;
  }
};

struct Person {
  string name;
  int height;
  double weight;
  Address address;

  bool operator==(const Person& other) const {
    return name == other.name && height == other.height && weight == other.weight && address == other.address;
  }
};

struct AddressHasher {
  size_t operator()(const Address& a) const{
	  size_t h1 = hs(a.city);
	  size_t h2 = hs(a.street);
	  size_t h3 = hi(a.building);
	  return h1*11*11+11*h2+h3;
  }
  hash<string> hs;
  hash<int> hi;
};

struct PersonHasher {
	size_t operator()(const Person& p) const {
		size_t h1 = hs(p.name);
		size_t h2 = hi(p.height);
		size_t h3 = hd(p.weight);
		size_t h4 = ha(p.address);
		return 17*17*17*h1+17*17*h2+17*h3+h4;
	}
	hash<string> hs;
	hash<int> hi;
	hash<double> hd;
	AddressHasher ha;
};

// СЃРіРµРЅРµСЂРёСЂРѕРІР°РЅС‹ РєРѕРјР°РЅРґРѕР№:
// $ sort -R /usr/share/dict/propernames | head -n 100
//
// http://www.freebsd.org/cgi/cvsweb.cgi/~checkout~/src/share/dict/propernames
const vector<string> WORDS = {
  "Kieran", "Jong", "Jisheng", "Vickie", "Adam", "Simon", "Lance",
  "Everett", "Bryan", "Timothy", "Daren", "Emmett", "Edwin", "List",
  "Sharon", "Trying", "Dan", "Saad", "Kamiya", "Nikolai", "Del",
  "Casper", "Arthur", "Mac", "Rajesh", "Belinda", "Robin", "Lenora",
  "Carisa", "Penny", "Sabrina", "Ofer", "Suzanne", "Pria", "Magnus",
  "Ralph", "Cathrin", "Phill", "Alex", "Reinhard", "Marsh", "Tandy",
  "Mongo", "Matthieu", "Sundaresan", "Piotr", "Ramneek", "Lynne", "Erwin",
  "Edgar", "Srikanth", "Kimberly", "Jingbai", "Lui", "Jussi", "Wilmer",
  "Stuart", "Grant", "Hotta", "Stan", "Samir", "Ramadoss", "Narendra",
  "Gill", "Jeff", "Raul", "Ken", "Rahul", "Max", "Agatha",
  "Elizabeth", "Tai", "Ellen", "Matt", "Ian", "Toerless", "Naomi",
  "Rodent", "Terrance", "Ethan", "Florian", "Rik", "Stanislaw", "Mott",
  "Charlie", "Marguerite", "Hitoshi", "Panacea", "Dieter", "Randell", "Earle",
  "Rajiv", "Ted", "Mann", "Bobbie", "Pat", "Olivier", "Harmon",
  "Raman", "Justin"
};

void TestSmoke() {
  vector<Person> points = {
    {"John", 180, 82.5, {"London", "Baker St", 221}},
    {"Sherlock", 190, 75.3, {"London", "Baker St", 221}},
  };

  unordered_set<Person, PersonHasher> point_set;
  for (const auto& point : points) {
    point_set.insert(point);
  }

  ASSERT_EQUAL(points.size(), point_set.size());
  for (const auto& point : points) {
    ASSERT_EQUAL(point_set.count(point), static_cast<size_t>(1));
  }
}

void TestPurity() {
  Person person = {"John", 180, 82.5, {"London", "Baker St", 221}};
  PersonHasher hasher;

  auto hash = hasher(person);
  for (size_t t = 0; t < 100; ++t) {
    ASSERT_EQUAL(hasher(person), hash);
  }
};

void TestDistribution() {
  auto seed = 42;
  mt19937 gen(seed);

  uniform_int_distribution<int> height_dist(150, 200);
  uniform_int_distribution<int> weight_dist(100, 240);  // [50, 120]
  uniform_int_distribution<int> building_dist(1, 300);
  uniform_int_distribution<int> word_dist(0, WORDS.size() - 1);

  PersonHasher hasher;

  // РІС‹Р±РёСЂР°РµРј С‡РёСЃР»Рѕ Р±Р°РєРµС‚РѕРІ РЅРµ РѕС‡РµРЅСЊ Р±РѕР»СЊС€РёРј РїСЂРѕСЃС‚С‹Рј С‡РёСЃР»РѕРј
  // (unordered_set, unordered_map РёСЃРїРѕР»СЊР·СѓСЋС‚ РїСЂРѕСЃС‚С‹Рµ С‡РёСЃР»Р° Р±Р°РєРµС‚РѕРІ
  // РІ СЂРµР°Р»РёР·Р°С†РёСЏС… GCC Рё Clang, РґР»СЏ РЅРµРїСЂРѕСЃС‚С‹С… С‡РёСЃРµР» Р±Р°РєРµС‚РѕРІ
  // РІРѕР·РЅРёРєР°СЋС‚ СЃР»РѕР¶РЅРѕСЃС‚Рё СЃРѕ СЃС‚Р°РЅРґР°СЂС‚РЅРѕР№ С…РµС€-С„СѓРЅРєС†РёРµР№ РІ СЌС‚РёС… СЂРµР°Р»РёР·Р°С†РёСЏС…)
  const size_t num_buckets = 2053;

  // РјС‹ С…РѕС‚РёРј, С‡С‚РѕР±С‹ С‡РёСЃР»Рѕ С‚РѕС‡РµРє РІ Р±Р°РєРµС‚Р°С… Р±С‹Р»Рѕ ~100'000
  const size_t perfect_bucket_size = 50;
  const size_t num_points = num_buckets * perfect_bucket_size;
  vector<size_t> buckets(num_buckets);
  for (size_t t = 0; t < num_points; ++t) {
    Person person;
    person.name = WORDS[word_dist(gen)];
    person.height = height_dist(gen);
    person.weight = weight_dist(gen) * 0.5;
    person.address.city = WORDS[word_dist(gen)];
    person.address.street = WORDS[word_dist(gen)];
    person.address.building = building_dist(gen);
    ++buckets[hasher(person) % num_buckets];
  }

  // РЎС‚Р°С‚РёСЃС‚РёРєР° РџРёСЂСЃРѕРЅР°:
  // https://en.wikipedia.org/wiki/Pearson's_chi-squared_test
  //
  // Р§РёСЃР»РµРЅРЅРѕР№ РјРµСЂРѕР№ СЂР°РІРЅРѕРјРµСЂРЅРѕСЃС‚Рё СЂР°СЃРїСЂРµРґРµР»РµРЅРёСЏ С‚Р°РєР¶Рµ РјРѕР¶РµС‚ РІС‹СЃС‚СѓРїР°С‚СЊ
  // СЌРЅС‚СЂРѕРїРёСЏ, РЅРѕ РґР»СЏ РµРµ РїРѕСЂРѕРіРѕРІ РЅРµС‚ С…РѕСЂРѕС€РµР№ СЃС‚Р°С‚РёСЃС‚РёС‡РµСЃРєРѕР№ РёРЅС‚РµСЂРїСЂРµС‚Р°С†РёРё
  double pearson_stat = 0;
  for (auto bucket_size : buckets) {
    size_t size_diff = bucket_size - perfect_bucket_size;
    pearson_stat +=
        size_diff * size_diff / static_cast<double>(perfect_bucket_size);
  }

  // РїСЂРѕРІРµСЂСЏРµРј СЂР°РІРЅРѕРјРµСЂРЅРѕСЃС‚СЊ СЂР°СЃРїСЂРµРґРµР»РµРЅРёСЏ РјРµС‚РѕРґРѕРј СЃРѕРіР»Р°СЃРёСЏ РџРёСЂСЃРѕРЅР°
  // СЃРѕ СЃС‚Р°С‚РёСЃС‚РёС‡РµСЃРєРѕР№ Р·РЅР°С‡РёРјРѕСЃС‚СЊСЋ 0.95:
  //
  // РµСЃР»Рё РїРѕРґСЃС‚Р°РІРёС‚СЊ РІРјРµСЃС‚Рѕ ++buckets[hasher(person) % num_buckets]
  // РІС‹СЂР°Р¶РµРЅРёРµ ++buckets[gen() % num_buckets], С‚Рѕ СЃ РІРµСЂРѕСЏС‚РЅРѕСЃС‚СЊСЋ 95%
  // ASSERT РЅРёР¶Рµ РѕС‚СЂР°Р±РѕС‚Р°РµС‚ СѓСЃРїРµС€РЅРѕ,
  //
  // С‚.Рє. СЃС‚Р°С‚РёСЃС‚РёРєР° РџРёСЂСЃРѕРЅР° РїСЂРёР±Р»РёР·РёС‚РµР»СЊРЅРѕ СЂР°СЃРїСЂРµРґРµР»РµРЅР° РїРѕ chi^2
  // СЃ С‡РёСЃР»РѕРј СЃС‚РµРїРµРЅРµР№ СЃРІРѕР±РѕРґС‹, СЂР°РІРЅС‹Рј num_buckets - 1,
  // Рё 95 РїСЂРѕС†РµРЅС‚РёР»СЊ СЌС‚РѕРіРѕ СЂР°СЃРїСЂРµРґРµР»РµРЅРёСЏ СЂР°РІРµРЅ:
  // >>> scipy.stats.chi2.ppf(0.95, 2052)
  const double critical_value = 2158.4981036918693;
  ASSERT(pearson_stat < critical_value);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSmoke);
  RUN_TEST(tr, TestPurity);
  RUN_TEST(tr, TestDistribution);

  return 0;
}
