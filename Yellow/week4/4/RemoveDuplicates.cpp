#include <iostream>
#include<vector>
#include<map>
#include<iterator>
#include<algorithm>
using namespace std;
template <typename T>
void RemoveDuplicates(vector<T>& elements){
	sort(elements.begin(),elements.end());
	auto it=unique(elements.begin(),elements.end());
	elements.erase(it,elements.end());
}

