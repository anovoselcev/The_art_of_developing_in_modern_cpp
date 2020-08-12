#include <iostream>
#include<map>
#include<set>
#include<string>
using namespace std;

int main() {
	map<int,set<string>> bus;
	int n,m,k=1,f=0;
	bus[0]={{"1"}};
	string s;
	set<string> in;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>m;
		for(int j=0;j<m;j++){
			cin>>s;
			in.insert(s);
		}
		for(auto x:bus){
			if(x.second==in){
				f=x.first;
				break;
			}
		}
		if(f!=0)
			cout<<"Already exists for "<<f<<endl;
			else{
				cout<<"New bus "<<k<<endl;
				bus[k]=in;
				k++;
			}
		in.clear();
		f=0;
	}
	return 0;
}
