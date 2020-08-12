#include <iostream>
#include<vector>
#include<map>
#include<utility>
using namespace std;
template<typename First,typename Second>
pair<First,Second> operator*(const pair<First,Second>& p1,const pair<First,Second> p2);
template<typename key,typename value>
map<key,value> operator*(const map<key,value>& m1,const map<key,value>& m2);
template<typename obj>
vector<obj> operator*(const vector<obj>& v1,const vector<obj>& v2);
template<typename obj> obj Sqr(obj var);


template<typename First,typename Second>
pair<First,Second> operator*(const pair<First,Second>& p1,const pair<First,Second> p2){
	pair<First,Second> p(p1.first*p2.first,p2.second*p2.second);
	return p;
}

template<typename key,typename value>
map<key,value> operator*(const map<key,value>& m1,const map<key,value>& m2){
	map<key,value> m;
	for(auto&x:m1)
		m[x.first]=m1.at(x.first)*m2.at(x.first);
	return m;
}

template<typename obj>
vector<obj> operator*(const vector<obj>& v1,const vector<obj>& v2){
	vector<obj> v(v1.size());
	for(unsigned i=0;i<v1.size();i++)
		v[i]=v1[i]*v2[i];
	return v;
}

template<typename obj>
obj Sqr(obj var){
	return var*var;
}
