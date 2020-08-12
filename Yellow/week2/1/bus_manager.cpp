#include"bus_manager.h"
void BusManager::AddBus(const string& bus, const vector<string>& stops) {
	  for(const auto&x:stops){
		  buses_to_stops[bus].push_back(x);
		  stops_to_buses[x].push_back(bus);
	  }
  }
BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
	  BusesForStopResponse p;
	  if(stops_to_buses.count(stop)==0){
		  p.stop="";
		  return p;
	  }
	  p.stop=stop;
	  p.buses=stops_to_buses.at(stop);
	  return p;
}
StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
	  StopsForBusResponse p;
	  if(buses_to_stops.count(bus)==0)
		  p.bus="";
	  else{
		  p.bus=bus;
		  p.stops=buses_to_stops.at(bus);
		  p.stb=stops_to_buses;
	  }
	  return p;

  }

  AllBusesResponse BusManager::GetAllBuses() const {
	  AllBusesResponse p;
	  p.book=buses_to_stops;
	  return p;
  }
