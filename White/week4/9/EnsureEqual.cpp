#include <iostream>
#include<sstream>
using namespace std;
void EnsureEqual(const string& left, const string& right){
	if(left!=right){
		stringstream s;
		s<<left<<" != "<<right;
		throw runtime_error(s.str());
	}
}
