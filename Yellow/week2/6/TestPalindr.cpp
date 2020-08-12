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

bool IsPalindrom(const string& s) {
	  for (size_t i = 0; i < s.size() / 2; ++i) {
	        if (s[i] != s[s.size() - i - 1]) {
	            return false;
	        }
	    }
	    return true;
}

void Test(){
	Assert(IsPalindrom("")==true,"1");
	Assert(IsPalindrom("a")==true,"2");
	Assert(IsPalindrom(" a ")==true,"3");
	Assert(IsPalindrom("a a")==true,"3");
	Assert(IsPalindrom("aba")==true,"4");
	Assert(IsPalindrom("abba")==true,"5");
	Assert(IsPalindrom("a b a")==true,"6");
	Assert(IsPalindrom("a b b a")==true,"7");
	Assert(IsPalindrom("adan")==false,"8");
	Assert(IsPalindrom("madamf")==false,"9");
	Assert(IsPalindrom("Fmadam")==false,"10");
	Assert(IsPalindrom("ab")==false,"10");
	Assert(IsPalindrom("abbbb")==false,"10");
	Assert(IsPalindrom("bbbba")==false,"10");
	Assert(IsPalindrom("bbabb")==true,"10");
	Assert(IsPalindrom("777778")==false,"10");
	Assert(IsPalindrom("777777")==true,"10");
}
void TestSymbols() {
  Assert(IsPalindrom("madam"), "madam");
  Assert(IsPalindrom("wasitacaroracatisaw"), "wasitacaroracatisaw");
  Assert(IsPalindrom("a a"), "a a");
}

void TestFirstLastSymbolIgnore() {
  Assert(!IsPalindrom("ZBCDmadamDCBA"), "ABCDmadamDCBA");
  Assert(!IsPalindrom("ABCDmadamDCBZ"), "ABCDmadamDCBZ");
}

void TestEarlyStop() {
  Assert(!IsPalindrom("wasitacaRoracatisaw"), "wasitacaRoracatisaw");
  Assert(!IsPalindrom("wasitacAroracatisaw"), "wasitacAroracatisaw");
  Assert(!IsPalindrom("wasitaCaroracatisaw"), "wasitaCaroracatisaw");
  Assert(!IsPalindrom("wasitAcaroracatisaw"), "wasitAcaroracatisaw");
  Assert(!IsPalindrom("wasiTacaroracatisaw"), "wasiTacaroracatisaw");
  Assert(!IsPalindrom("wasItacaroracatisaw"), "wasItacaroracatisaw");
  Assert(!IsPalindrom("waSitacaroracatisaw"), "waSitacaroracatisaw");
  Assert(!IsPalindrom("wAsitacaroracatisaw"), "wAsitacaroracatisaw");
  Assert(!IsPalindrom("wasitacaRracatisaw"), "wasitacaRoracatisaw");
  Assert(!IsPalindrom("wasitacArracatisaw"), "wasitacAroracatisaw");
  Assert(!IsPalindrom("wasitaCarracatisaw"), "wasitaCaroracatisaw");
  Assert(!IsPalindrom("wasitAcarracatisaw"), "wasitAcaroracatisaw");
  Assert(!IsPalindrom("wasiTacarracatisaw"), "wasiTacaroracatisaw");
  Assert(!IsPalindrom("wasItacarracatisaw"), "wasItacaroracatisaw");
  Assert(!IsPalindrom("waSitacarracatisaw"), "waSitacaroracatisaw");
  Assert(!IsPalindrom("wAsitacarracatisaw"), "wAsitacaroracatisaw");

}

void TestIgnoreSpaces() {
  Assert(!IsPalindrom(" ABCCBA"), " ABCCBA");
  Assert(!IsPalindrom("ABCCBA "), "ABCCBA ");
  Assert(!IsPalindrom("ABCCB A"), "ABCCB A");
  Assert(!IsPalindrom("A BCCBA"), "A BCCBA");
  Assert(!IsPalindrom("AB CCBA"), "AB CCBA");
  Assert(!IsPalindrom("ABCC BA"), "ABCC BA");
  Assert(!IsPalindrom("AB CCBA"), "AB CCBA");
  Assert(!IsPalindrom("ABCcBA"), "ABCcBA");
  Assert(!IsPalindrom("ABC CbA"), "ABC CbA");
  Assert(!IsPalindrom("ABC cbA"), "ABC cbA");
}
int main() {
  TestRunner runner;
  runner.RunTest(Test," ");
  runner.RunTest(TestSymbols," ");
  runner.RunTest(TestFirstLastSymbolIgnore," ");
  runner.RunTest(TestEarlyStop," ");
  runner.RunTest(TestIgnoreSpaces," ");
  return 0;
}
