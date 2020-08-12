#include <iostream>
#include<vector>
using namespace std;

int main() {
	int x;
	vector <int> v;
	cin>>x;
	while(x!=0){
		v.push_back(x%2);
		x/=2;
	}
	for(int i=v.size()-1;i>=0;i--)
		cout<<v[i];
	return 0;
}
