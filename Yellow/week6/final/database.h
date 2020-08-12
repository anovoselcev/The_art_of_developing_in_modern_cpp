#pragma once
#include<map>
#include<iostream>
#include<sstream>
#include<set>
#include<algorithm>
#include<vector>
#include<utility>
#include"date.h"

using namespace std;

class Database{
public:
	void Add(const Date& date,const string& event);
	void Print(ostream& os) const;
	template<typename function>
	int RemoveIf(function p){
		int n=0;
		vector<map<Date,vector<string>>::iterator> vvit;
		for(auto j=begin(list);j!=end(list);j++){
			vector<vector<string>::iterator> vit;
			/*auto lit=remove_if(begin(list[j->first]),end(list[j->first]),[p,j](const string& event){
				return p(j->first,event);
			});*/
			auto lit=stable_partition(begin(list[j->first]),end(list[j->first]),[p,j](const string event){
				return !p(j->first,event);
			});
			n+=distance(lit,end(list[j->first]));
			for(auto i=lit;i!=end(list[j->first]);i++)
				num[j->first][*i]=0;
			list[j->first].erase(lit,end(list[j->first]));
			if(list[j->first].size()==0)
				vvit.push_back(j);
		}
		for(const auto&x:vvit)
			list.erase(x);
		return n;
	}
	template<typename function>
	vector<pair<Date,string>> FindIf(function p)const{
		vector<pair<Date,string>> enter;
		for(const auto&x:list){
			auto it=begin(x.second);
			while(it!=end(x.second)){
				it=find_if(it,end(x.second),[p,x](const string& event ){
					return p(x.first,event);
				});
				if(it!=end(x.second)){
					enter.push_back({x.first,*it});
					it++;
				}
			}
		}
		return enter;
	}
	pair<Date,string> Last(const Date& date) const;

private:
	map<Date,vector<string>> list;
	map<Date,map<string,int>> num;
};

ostream& operator<<(ostream& os,const  pair<Date,string>& voc);

string Transform(const Date& date);
void TestDatabase();
