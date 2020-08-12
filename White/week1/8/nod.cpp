
#include <iostream>
using namespace std;

int main() {
	int a,b;
	cin>>a>>b;
	if(a>b)
		swap(b,a);
	while(b%a!=0){
		b=b%a;
		swap(b,a);
	}
	cout<<a;
	return 0;
}
