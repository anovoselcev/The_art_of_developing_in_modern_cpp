#include <algorithm>
#include <memory>
#include <vector>
#include<iterator>
#include"../../TestRunner/test_runner.h"
using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end){
	if(range_end-range_begin<2)
		return;
	vector<typename RandomIt::value_type> elements(make_move_iterator(range_begin),
			make_move_iterator(range_end));
	vector<typename RandomIt::value_type> dst;
	auto it1=begin(elements)+elements.size()/3;
	auto it2=begin(elements)+2*elements.size()/3;
	MergeSort(elements.begin(),it1);
	MergeSort(it1,it2);
	MergeSort(it2,elements.end());
	merge(make_move_iterator(elements.begin()),
			make_move_iterator(it1),
			make_move_iterator(it1),
			make_move_iterator(it2),
			back_inserter(dst));
	merge(make_move_iterator(dst.begin()),
			make_move_iterator(dst.end()),
			make_move_iterator(it2),
			make_move_iterator(elements.end()),
			range_begin);
}


/*template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end){
	if(range_end-range_begin<2)
		return;
	vector<typename RandomIt::value_type> elements(move(range_begin), move(range_end));
	vector<typename RandomIt::value_type> dst;
	auto it=begin(elements)+elements.size()/2;
	MergeSort(begin(elements),it);
	MergeSort(it,end(elements));
	merge(begin(elements),it,it,end(elements),range_begin);
}*/
void TestIntVector() {
  vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
  MergeSort(begin(numbers), end(numbers));
  ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  return 0;
}
