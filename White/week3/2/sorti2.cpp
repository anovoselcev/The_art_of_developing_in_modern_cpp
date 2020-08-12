#include <iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<string>
using namespace std;

int main() {
	int n;
	cin>>n;
	vector<string> v(n);
	for(auto&x:v)
		cin>>x;
	sort(v.begin(),v.end(),[](string x,string y){
		for(auto& a:x)
			a=tolower(a);
		for(auto& a:y)
			a=tolower(a);
		return x<y;
	});
	for(const auto &x:v)
		cout<<x<<" ";
	return 0;
}
