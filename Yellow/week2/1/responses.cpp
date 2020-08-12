#include"responses.h"

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
	if(r.stop.empty())
		os<<"No stop";
	else{
	for(const auto&x:r.buses)
		os<<x<<" ";
	}
  return os;
}

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
	if(r.bus.empty())
		os<<"No bus";
	else{
		unsigned i=1;
		for(const auto&x:r.stops){
			os<<"Stop "<<x<<": ";
			for(const auto&y:r.stb.at(x)){
				if((r.stb.at(x).size()==1)&&(y==r.bus))
					os<<"no interchange";
				else
					if(y!=r.bus)
						os<<y<<" ";
			}
			if(i<r.stops.size())
				os<<endl;
			i++;
		}
	}
  return os;
}

ostream& operator << (ostream& os, const AllBusesResponse& r) {
	unsigned i=1;
	if(r.book.empty())
		os<<"No buses";
	else{
		for(const auto&x:r.book){
			os<<"Bus "<<x.first<<":";
			for(const auto&y:x.second)
				os<<" "<<y;
			if(i<r.book.size())
				os<<endl;
			i++;
		}
	}
  return os;
}
