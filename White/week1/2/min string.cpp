#include <iostream>
#include <string>
using namespace std;

int main() {
	string a,b,c,min;
	cin>>a>>b>>c;
	min=a;
	if(b<min || c<min){
		if(b<c)
			min=b;
		else
			min=c;
	}
	cout <<min;
	return 0;
}
