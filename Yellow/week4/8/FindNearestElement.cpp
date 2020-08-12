#include <iostream>
#include<set>
#include<iterator>
#include<algorithm>
using namespace std;

set<int>::const_iterator FindNearestElement(
    const set<int>& numbers,
    int border){
	auto it=numbers.lower_bound(border);
	if(numbers.begin()==numbers.end())
		return it;
	else if(it==numbers.end())
		return --it;
	else if((it!=begin(numbers))&&(border-*prev(it)<=*it-border))
		return prev(it);
	else
		return it;
}
