#include"database.h"
void Database::Add(const Date& date,const string& event){
	if(num[date][event]==0){
		list[date].push_back(event);
	}
	num[date][event]=1;
}
void Database::Print(ostream& os) const{
	for(const auto&x:list){
		for(const auto&y:x.second)
			os<<x.first<<" "<<y<<endl;
	}
}

string Transform(const Date& date){
	string d="";
	if(date.year<1000)
		d+="0";
	if(date.year<100)
		d+="0";
	if(date.year<10)
		d+="0";
	d+=to_string(date.year);
	d+="-";
	if(date.month<10)
		d+="0";
	d+=to_string(date.month);
	d+="-";
	if(date.day<10)
		d+="0";
	d+=to_string(date.day);
	return d;
}

pair<Date,string> Database::Last(const Date& date) const{
	auto it=list.lower_bound(date);
	if(it->first==date){
		return {it->first,*(--it->second.end())};
	}
	else if(it!=list.begin()){
		it--;
		return {it->first,*(--it->second.end())};
	}
	else
		throw invalid_argument("");
}

ostream& operator<<(ostream& os,const  pair<Date,string>& voc){
	Date d={-1,-1,-1};
	if(!(voc.first==d))
		os<<voc.first<<" "<<voc.second;
	else
		os<<voc.second;
	return os;
}
