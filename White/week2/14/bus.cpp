#include <iostream>
#include<map>
#include<vector>
#include<string>
using namespace std;


int main() {
	map<string,vector<string>> buses;
	map<string,vector<string>> stops;
	int n,m;
	string s,name,stop;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>s;
		if(s=="NEW_BUS"){
			cin>>name;
			cin>>m;
			for(int j=0;j<m;j++){
				cin>>stop;
				buses[name].push_back(stop);
				stops[stop].push_back(name);
			}
		}
		if(s=="BUSES_FOR_STOP"){
			cin>>stop;
			if(stops[stop].size()==0){
				cout<<"No stop"<<endl;
				stops.erase(stop);
			}
			else{
				for(auto x:stops[stop])
					cout<<x<<" ";
				cout<<endl;
			}
		}
		if(s=="STOPS_FOR_BUS"){
			cin>>name;
			if(buses[name].size()==0){
				cout<<"No bus"<<endl;
				buses.erase(name);
			}
			else{
				for(auto x:buses[name]){
					cout<<"Stop "<<x<<":";
					for(auto y:stops[x]){
						if((stops[x].size()==1)&&(y==name))
							cout<<" no interchange";
						else
							if(y!=name)
							cout<<" "<<y;
					}
					cout<<endl;
				}
			}
		}
		if(s=="ALL_BUSES"){
			if(buses.size()==0)
				cout<<"No buses"<<endl;
			else{
				for(auto x:buses){
					cout<<"Bus "<<x.first<<":";
					for(auto y:x.second)
						cout<<" "<<y;
					cout<<endl;
				}
			}
		}
	}
	return 0;
}
