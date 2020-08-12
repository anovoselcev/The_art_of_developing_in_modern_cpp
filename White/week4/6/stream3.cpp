#include <iostream>
#include<fstream>
#include<iomanip>
using namespace std;
int main() {
	int n,m,k;
	ifstream input("input.txt");
	input>>n;
	input>>m;
		for(int i=0;(i<n);i++){
			for(int j=0;(j<m);j++){
				input>>k;
				input.ignore(1);
				cout<<setw(10)<<k;
				if(j!=m-1)
					cout<<" ";
			}
		if(i!=n-1)
			cout<<endl;
		}

	return 0;
}
