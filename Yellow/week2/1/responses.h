#pragma once
#include"query.h"
struct BusesForStopResponse {
	vector<string> buses;
	string stop;
};
ostream& operator << (ostream& os, const BusesForStopResponse& r);
struct StopsForBusResponse {
	string bus;
	vector<string> stops;
	map<string,vector<string>> stb;
};
ostream& operator << (ostream& os, const StopsForBusResponse& r);
struct AllBusesResponse {
	map<string,vector<string>> book;
};
ostream& operator << (ostream& os, const AllBusesResponse& r);
