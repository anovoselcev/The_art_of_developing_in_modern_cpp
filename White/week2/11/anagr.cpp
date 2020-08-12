#include <iostream>
#include<map>
#include<string>
using namespace std;
void BuildCharCounters(const string &s1,const string &s2){
	map<char,int> a1,a2;
	for(auto &i:s1)
		a1[i]++;
	for(auto &i:s2)
			a2[i]++;
	if(a1==a2)
		cout<<"YES"<<endl;
	else
		cout<<"NO"<<endl;
	}
int main() {
	int n;
	string s1,s2;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>s1>>s2;
		BuildCharCounters(s1,s2);
	}
	return 0;
}
