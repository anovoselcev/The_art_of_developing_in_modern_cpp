#include"query.h"
istream& operator >> (istream& is, Query& q) {
	map<string,QueryType> m={{"NEW_BUS",QueryType::NewBus},{"BUSES_FOR_STOP",QueryType::BusesForStop},{"STOPS_FOR_BUS",QueryType::StopsForBus},{"ALL_BUSES",QueryType::AllBuses}};
	string s;
	is>>s;
	q.stops.clear();
	q.type=m.at(s);
	 switch (q.type) {
	    case QueryType::NewBus:{
	      is>>q.bus;
	      int n;
	      string s1;
	      is>>n;
	      for(int i=0;i<n;i++){
	    	  is>>s1;
	    	  q.stops.push_back(s1);
	      }
	      break;}
	    case QueryType::BusesForStop:
	      is>>q.stop;
	      break;
	    case QueryType::StopsForBus:
	      is>>q.bus;
	      break;
	    default:break;
	    }

  return is;
}
