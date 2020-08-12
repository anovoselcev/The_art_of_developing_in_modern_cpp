#include "airline_ticket.h"
#include "test_runner.h"

#include<algorithm>
#include<iomanip>
#include<utility>
#include<iterator>
using namespace std;

bool operator==(const Date& date1,const Date& date2);
bool operator==(const pair<string,string>& p1,const pair<string,string>& p2);
bool operator<(const Date& date1, const Date& date2);
bool operator<(const Time& time1, const Time& time2);
ostream& operator<<(ostream& os, const Date& date);
ostream& operator<<(ostream& os, const Time& time);
istream& operator>>(istream& is,Time& time);
istream& operator>>(istream& is,Date& date);
bool operator==(const Time& time1,const Time& time2);


#define UPDATE_FIELD(ticket, field, values) 				\
		if(values.find(#field)!=end(values)){				\
			istringstream is(values.find(#field)->second);	\
			is>>ticket.field;								\
}

void TestUpdate() {
  AirlineTicket t;
  t.price = 0;

  const map<string, string> updates1 = {
    {"departure_date", "2018-2-28"},
    {"departure_time", "17:40"},
  };
 UPDATE_FIELD(t, departure_date, updates1);
 UPDATE_FIELD(t, departure_time, updates1);
 UPDATE_FIELD(t, price, updates1);

  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 0);

  const map<string, string> updates2 = {
    {"price", "12550"},
    {"arrival_time", "20:33"},
  };
  UPDATE_FIELD(t, departure_date, updates2);
  UPDATE_FIELD(t, departure_time, updates2);
  UPDATE_FIELD(t, arrival_time, updates2);
  UPDATE_FIELD(t, price, updates2);

  // updates2 РЅРµ СЃРѕРґРµСЂР¶РёС‚ РєР»СЋС‡РµР№ "departure_date" Рё "departure_time", РїРѕСЌС‚РѕРјСѓ
  // Р·РЅР°С‡РµРЅРёСЏ СЌС‚РёС… РїРѕР»РµР№ РЅРµ РґРѕР»Р¶РЅС‹ РёР·РјРµРЅРёС‚СЊСЃСЏ
  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 12550);
  ASSERT_EQUAL(t.arrival_time, (Time{20, 33}));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestUpdate);
}


bool operator==(const Date& date1,const Date& date2){
	return (date1.day==date2.day)&&(date1.month==date2.month)&&(date1.year==date2.year);
}

bool operator<(const Date& date1, const Date& date2){
	if(date1.year!=date2.year)
		return date1.year<date2.year;
	else if(date1.month!=date2.month)
		return date1.month<date2.month;
	else
		return date1.day<date2.day;
}

bool operator<(const Time& time1, const Time& time2){
	if(time1.hours!=time2.hours)
		return time1.hours<time2.hours;
	else
		return time1.minutes<time2.minutes;
}

ostream& operator<<(ostream& os, const Date& date){
	os<<setw(4) << setfill('0')<<date.year<<"-"<<setw(2) << setfill('0')<<date.month<<"-"<<setw(2) << setfill('0')<<date.day;
	return os;
}

istream& operator>>(istream& is,Time& time){
	int x,y;
	char s;
	is>>x>>s>>y;
	time.hours=x;
	time.minutes=y;
	return is;
}

istream& operator>>(istream& is,Date& date){
	int x,y,z;
	char s1,s2;
	is>>x>>s1>>y>>s2>>z;
	date.year=x;
	date.month=y;
	date.day=z;
	return is;
}


ostream& operator<<(ostream& os, const Time& time){
	os<<time.hours<<':'<<time.minutes;
	return os;
}

bool operator==(const Time& time1,const Time& time2){
	return (time1.hours==time2.hours)&&(time1.minutes==time2.minutes);
}

