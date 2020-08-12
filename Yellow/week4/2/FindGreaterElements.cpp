#include <iostream>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;

template <typename T>
vector<T> FindGreaterElements(const set<T>& elements, const T& border){
	vector<T> v;
	auto f=find_if(begin(elements),end(elements),[border](const T&a){return a>border;});
		for(f;f!=end(elements);f++)
			v.push_back(*f);
	return v;
}
