#include <iostream>
#include<fstream>
using namespace std;

int main() {
	//ifstream input("input.txt");
	string line;
	//while(getline(input,line)){
		//cout<<line<<endl;
	//}
	ifstream input1("input.txt");
	ofstream output("output.txt");
	while(getline(input1,line)){
		output<<line<<endl;
	}

		return 0;
}
