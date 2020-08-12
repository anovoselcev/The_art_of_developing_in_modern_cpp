#include <iostream>
#include<fstream>
#include<iomanip>
#include<vector>
using namespace std;

int main() {
	vector<double> sline;
	double s;
	ifstream input("input.txt");
	cout<<fixed<<setprecision(3);
	while(input){
		input>>s;
		if(input)
			sline.push_back(s);
	}
	for(const auto&x:sline)
		cout<<x<<endl;
	return 0;
}
