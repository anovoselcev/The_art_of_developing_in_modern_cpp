#pragma once
#include<iostream>
#include<sstream>
#include<iomanip>
class Date{
public:
	int day,month,year;
	Date(int x,int y,int z);
	Date();
};
bool operator<(const Date& date1,const Date& date2);

bool operator==(const Date& date1,const Date& date2);

std::ostream& operator<<(std::ostream& os,const Date& date);
