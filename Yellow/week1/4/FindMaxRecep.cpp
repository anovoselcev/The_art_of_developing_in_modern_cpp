#include <iostream>
#include<map>
#include<vector>
#include<algorithm>
#include <inttypes.h>
#include<tuple>
bool operator<(const Region& r1,const Region& r2){
	return tie(r1.std_name,r1.parent_std_name,r1.names,r1.population)<tie(r2.std_name,r2.parent_std_name,r2.names,r2.population);
}

int FindMaxRepetitionCount(const vector<Region>& regions){
	map<Region,int> num;
	int n=0;
	if(regions.size()==0)
		return 0;
	for(const auto&x:regions){
		num[x]++;
		if(num[x]>n)
			n=num[x];
	}
	return n;
}

