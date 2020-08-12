#include <iostream>
#include<deque>
#include<map>
#include<sstream>
#include<algorithm>
#include<stdexcept>
#include<exception>
#include"profile.h"
using namespace std;

class Data{
public:
	Data(){}
	Data(const int64_t& _t,
		const string& _h,
		const int& _c,
		const int& _r):
		time(_t),	hotel(_h),	client_id(_c),	rooms(_r){}
	int64_t time;
	string hotel;
	int client_id;
	int rooms;

};
istream& operator>>(istream& is,Data& _d){
	int64_t time;
	string hotel;
	int client_id;
	int rooms;
	cin>>time>>hotel>>client_id>>rooms;
	_d = Data{time,hotel,client_id,rooms};
	return is;
}
class Booking{
public:
	Booking():
	time(0){}

	void Book(const Data& d){
		//LOG_DURATION("BOOK")
		time = max(time,d.time);
		while(data.size()>0){
			if(time - data[data.size()-1].time >= 86400){
				if(hotels[data[data.size()-1].hotel][data[data.size()-1].client_id]>0){
					hotels[data[data.size()-1].hotel][data[data.size()-1].client_id]--;
					res_hotels[data[data.size()-1].hotel]--;
				}
				if(res_rooms[data[data.size()-1].hotel]>0){
					res_rooms[data[data.size()-1].hotel]-=data[data.size()-1].rooms;
				}
				data.pop_back();
			}
			else
				break;
		}
		data.push_front(d);
		if(hotels[d.hotel][d.client_id] == 0){
			hotels[d.hotel][d.client_id] =1;
			res_hotels[d.hotel]++;
		}
		res_rooms[d.hotel]+=d.rooms;
	}
	int Clients(const string& _hotel_name) const{
		//LOG_DURATION("CLIENTS")
		try{
			return res_hotels.at(_hotel_name);
		}
		catch(out_of_range &e){
			return 0;
		}
	}
	int Rooms(const string& _hotel_name) const{
		//LOG_DURATION("ROOMS")
		try{
			return res_rooms.at(_hotel_name);
		}
		catch(out_of_range&){
			return 0;
		}
	}

private:
	deque<Data> data;
	map<string,int> res_hotels;
	map<string,int> res_rooms;
	map<string,map<int,int>> hotels;
	int64_t time;

};

int main() {
	//LOG_DURATION("MAIN")
	ios::sync_with_stdio(false);
	  cin.tie(nullptr);
	Booking b;
	int q;
	cin>>q;
	string cmd;
	for(int i=0;i<q;++i){
		cin>>cmd;
		if(cmd == "BOOK"){
			Data d;
			cin>>d;
			b.Book(d);
		}
		else if(cmd == "CLIENTS"){
			string h;
			cin>>h;
			cout<<b.Clients(h)<<'\n';
		}
		else if(cmd == "ROOMS"){
			string h;
			cin>>h;
			cout<<b.Rooms(h)<<'\n';
		}
	}
	return 0;
}
