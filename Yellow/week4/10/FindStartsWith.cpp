#include <iostream>
#include<iterator>
#include<vector>
#include<algorithm>
#include<utility>
#include<string>
#include<typeinfo>
using namespace std;


template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
    RandomIt range_begin, RandomIt range_end,
    const string& prefix){
	string s="";
	s+=prefix;
	 auto first = std::lower_bound(range_begin, range_end, s);
	  ++s.back();
	  auto last = std::lower_bound(range_begin, range_end, s);
	  return { first, last };
}

