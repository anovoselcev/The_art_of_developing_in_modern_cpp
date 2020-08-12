#include <iostream>
using namespace std;

int main() {
	uint64_t m=0,r,n,w,h,d;
	cin>>n>>r;
	for(uint64_t i=0;i<n;i++){
		cin>>w>>h>>d;
		m+=w*h*d*r;
	}
	cout<<m;
	return 0;
}
