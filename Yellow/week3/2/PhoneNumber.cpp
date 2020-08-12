#include <iostream>
#include"phone_number.h"
using namespace std;

PhoneNumber::PhoneNumber(const string &international_number){
	country_code_="";
	city_code_="";
	local_number_="";
	unsigned i=0;
	if(international_number[0]!='+')
		throw invalid_argument("");
	else{
		for(i=1;(i<international_number.size())&&(international_number[i]!='-');i++)
			country_code_+=international_number[i];
		i++;
		for(i;(i<international_number.size())&&(international_number[i]!='-');i++)
			city_code_+=international_number[i];
		i++;
		for(i;(i<international_number.size());i++)
			local_number_+=international_number[i];
	}
	if((i!=international_number.size())||(country_code_.empty())||(city_code_.empty())||(local_number_.empty()))
		throw invalid_argument("");
}
string PhoneNumber::GetCountryCode() const{return country_code_; }
string PhoneNumber::GetCityCode() const{return city_code_;}
string PhoneNumber::GetLocalNumber() const{return local_number_;}
string PhoneNumber::GetInternationalNumber() const{
	return "+"+country_code_+"-"+city_code_+"-"+local_number_;}
