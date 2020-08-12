#include <iostream>
#include<map>
#include<exception>
using namespace std;
template<typename key,typename value>
value & GetRefStrict(map<key,value>& m,const key& k){
	if(m.count(k)==0)
		throw runtime_error("");
	else
		return m.at(k);
}
