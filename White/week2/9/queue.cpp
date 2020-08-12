#include <iostream>
#include<string>
#include<vector>
using namespace std;

int main() {
	vector<bool> q;
	int n,k,m=0;
	string s;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>s;
		if("WORRY"==s){
			cin>>k;
			q[k]=true;
		}
		if("QUIET"==s){
			cin>>k;
			q[k]=false;
		}
		if("COME"==s){
			cin>>k;
			q.resize(q.size()+k,false);
		}
		if("WORRY_COUNT"==s){
			for(auto j:q){
				if(j==true)
					m++;
				}
			cout<<m<<endl;
			m=0;
		}
	}
	return 0;
}
