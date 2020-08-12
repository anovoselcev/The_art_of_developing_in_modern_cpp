#include <iostream>
#include<string>
#include<set>
using namespace std;

int main() {
	set<string> a;
	int n;
	string s;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>s;
		a.insert(s);
	}
	cout<<a.size();
	return 0;
}
