#include <iostream>
#include<vector>
#include<algorithm>
using namespace std;

/*template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end){
	if(range_end-range_begin<2)
		return;
	vector<typename RandomIt::value_type> elements(range_begin, range_end);
	vector<typename RandomIt::value_type> dst;
	auto it1=begin(elements)+elements.size()/3;
	auto it2=begin(elements)+2*elements.size()/3;
	MergeSort(begin(elements),it1);
	MergeSort(it1,it2);
	MergeSort(it2,end(elements));
	merge(begin(elements),it1,it1,it2,back_inserter(dst));
	merge(dst.begin(),dst.end(),it2,end(elements),range_begin);
}*/


template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end){
	if(range_end-range_begin<2)
		return;
	vector<typename RandomIt::value_type> elements(range_begin, range_end);
	vector<typename RandomIt::value_type> dst;
	auto it=begin(elements)+elements.size()/2;
	MergeSort(begin(elements),it);
	MergeSort(it,end(elements));
	merge(begin(elements),it,it,end(elements),range_begin);
}

