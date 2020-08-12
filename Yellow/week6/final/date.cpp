#include"date.h"
using namespace std;
Date::Date(){}
Date::Date(int x,int y,int z){
	year=x;
	month=y;
	day=z;
}

bool operator<(const Date& date1,const Date& date2){
	if(date1.year<date2.year)
		return true;
	if(date1.year>date2.year)
		return false;
	if(date1.month<date2.month)
		return true;
	if(date1.month>date2.month)
		return false;
	else
		return date1.day<date2.day;
}

bool operator==(const Date& date1,const Date& date2){
	return (date1.year==date2.year)&&(date1.month==date2.month)&&(date1.day==date2.day);
}

std::ostream& operator<<(std::ostream& os,const Date& date){
	os<<setw(4) << setfill('0')<<date.year<<"-"<<setw(2) << setfill('0')<<date.month<<"-"<<setw(2) << setfill('0')<<date.day;
	return os;
}
