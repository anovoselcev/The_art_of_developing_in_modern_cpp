#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
      os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

string FindNameByYear(const map<int, string>& names, int year) {
  string name;  // изначально имя неизвестно

  // перебираем всю историю по возрастанию ключа словаря, то есть в хронологическом порядке
  for (const auto& item : names) {
    // если очередной год не больше данного, обновляем имя
    if (item.first <= year) {
      name = item.second;
    } else {
      // иначе пора остановиться, так как эта запись и все последующие относятся к будущему
      break;
    }
  }

  return name;
}

class Person {
public:
  void ChangeFirstName(int year, const string& first_name) {
    first_names[year] = first_name;
  }
  void ChangeLastName(int year, const string& last_name) {
    last_names[year] = last_name;
  }
  string GetFullName(int year) {
    // получаем имя и фамилию по состоянию на год year
    const string first_name = FindNameByYear(first_names, year);
    const string last_name = FindNameByYear(last_names, year);

    // если и имя, и фамилия неизвестны
    if (first_name.empty() && last_name.empty()) {
      return "Incognito";

    // если неизвестно только имя
    } else if (first_name.empty()) {
      return last_name + " with unknown first name";

    // если неизвестна только фамилия
    } else if (last_name.empty()) {
      return first_name + " with unknown last name";

    // если известны и имя, и фамилия
    } else {
      return first_name + " " + last_name;
    }
  }

private:
  map<int, string> first_names;
  map<int, string> last_names;
};

void Test1(){
	Person p;
	Assert(p.GetFullName(1900)=="Incognito"," ");
	Assert(p.GetFullName(1990)=="Incognito"," ");
	p.ChangeFirstName(1965, "Polina");
	Assert(p.GetFullName(1965)=="Polina with unknown last name"," ");
	p.ChangeLastName(1967, "Sergeeva");
	Assert(p.GetFullName(1990)=="Polina Sergeeva"," ");
	p.ChangeFirstName(1970, "Appolinaria");
	Assert(p.GetFullName(1969)=="Polina Sergeeva"," ");
	Assert(p.GetFullName(1970)=="Appolinaria Sergeeva"," ");
	p.ChangeLastName(1968, "Volkova");
	Assert(p.GetFullName(1968)=="Polina Volkova"," ");
	Assert(p.GetFullName(1970)=="Appolinaria Volkova"," ");
	Assert(p.GetFullName(1990)=="Appolinaria Volkova"," ");
}
void Test2(){
	Person p;
	Assert(p.GetFullName(1910)=="Incognito"," ");
	Assert(p.GetFullName(1920)=="Incognito"," ");
	p.ChangeLastName(1965, "Polina");
	Assert(p.GetFullName(1965)=="Polina with unknown first name"," ");
	Assert(p.GetFullName(1920)=="Incognito"," ");
	p.ChangeFirstName(1969, "Polina");
	Assert(p.GetFullName(1967)=="Polina with unknown first name"," ");
	Assert(p.GetFullName(1980)=="Polina Polina"," ");
}

int main() {
  TestRunner runner;
  runner.RunTest(Test1," ");
  runner.RunTest(Test2," ");
  return 0;
}
