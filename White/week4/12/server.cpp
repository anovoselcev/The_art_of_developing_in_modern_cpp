#include <iostream>
#include <system_error>
using namespace std;

class TimeServer {
public:
  string GetCurrentTime(){
	  try{
		  LastFetchedTime = AskTimeServer();
		  return LastFetchedTime;
	  }
	  catch(const system_error& e){
		  return LastFetchedTime;
	  }
  }
private:
  string LastFetchedTime = "00:00:00";
};
