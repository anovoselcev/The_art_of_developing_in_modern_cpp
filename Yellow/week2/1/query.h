#pragma once
#include<iostream>
#include<sstream>
#include<map>
#include<vector>
#include<string>
using namespace std;
enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};
struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};
istream& operator >> (istream& is, Query& q);
