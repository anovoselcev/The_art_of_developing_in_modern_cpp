#include<iostream>
#include<sstream>
#include <algorithm>
#include <string>
#include <vector>
#include<map>
#include<set>

using namespace std;

class Learner {
 private:
  vector<string> dict;
  map<string,int> num;
  set<string> voc;

 public:
  int Learn(const vector<string>& words) {
    int newWords = 0;
    for (const auto& word : words) {
      if (num[word]==0) {
        ++newWords;
        num[word]++;
        voc.insert(word);
      }
    }
    return newWords;
  }

  vector<string> KnownWords() {
	 vector<string> v;
	 v.assign(begin(voc),end(voc));
    return v;
  }
};
