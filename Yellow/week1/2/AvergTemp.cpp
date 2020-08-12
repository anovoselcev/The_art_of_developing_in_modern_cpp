#include <iostream>
#include<vector>
using namespace std;

int main() {
	int n;
	int64_t a=0;
	cin>>n;
	vector<int> temp(n);
	vector<int> res;
	for(int i=0;i<n;i++){
		cin>>temp[i];
		a+=temp[i];
	}
	a=a/static_cast<int>(temp.size());
	for(int i=0;i<n;i++){
		if(temp[i]>a)
			res.push_back(i);
	}
	cout<<res.size()<<endl;
	for(unsigned int i=0;i<res.size();i++){
		if(i!=res.size()-1)
			cout<<res[i]<<" ";
		else
			cout<<res[i];
	}
	return 0;
}
