#include <iostream>
#include<vector>
#include<map>
#include<string>
using namespace std;

int main() {
	map<int,vector<string>> way;
	vector<string> ex;
	string s;
	way[0]={"."};
	int n,m,k=1,f=0;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>m;
		for(int j=0;j<m;j++){
			cin>>s;
			ex.push_back(s);
		}
		for(auto x:way){
			if(x.second==ex){
				f=x.first;
				break;
			}
		}
		if(f!=0)
			cout<<"Already exists for "<<f<<endl;
			else{
				way[k]=ex;
				cout<<"New bus "<<k<<endl;
				k++;
			}
		f=0;
		ex.clear();
	}
	return 0;
}
