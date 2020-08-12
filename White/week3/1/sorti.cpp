#include <iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

int main() {
	int n,k;
	vector<int> v;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>k;
		v.push_back(k);
	}
	sort(v.begin(),v.end(),[](int x,int y){return abs(x)<abs(y);});
	for(const auto &x:v)
		cout<<x<<" ";
	return 0;
}
