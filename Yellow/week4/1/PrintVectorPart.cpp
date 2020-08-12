#include <iostream>
#include<vector>
#include<algorithm>
using namespace std;

void PrintVectorPart(const vector<int>& numbers){
	auto f=find_if(begin(numbers),end(numbers),[](const int& a){return a<0;});
	while(f!=begin(numbers)){
		f--;
		cout<<*f<<" ";
	}
}
