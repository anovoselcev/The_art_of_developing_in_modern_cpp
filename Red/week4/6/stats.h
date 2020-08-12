#pragma once

#include "http_request.h"
////
#include <string_view>
#include <map>
#include<array>
#include<iostream>
using namespace std;

class Stats {
public:
  Stats();
  void AddMethod(string_view method);
  void AddUri(string_view uri);
  const map<string_view, int>& GetMethodStats() const;
  const map<string_view, int>& GetUriStats() const;
private:
  map<string_view, int> ms;
  map<string_view, int> us;
};

HttpRequest ParseRequest(string_view line);
