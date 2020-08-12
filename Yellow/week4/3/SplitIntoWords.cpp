#include <iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

vector<string> SplitIntoWords(const string& s){
	vector<string> v;
	string w="";
	for(string::const_iterator i=s.begin();i!=s.end();i++){
		if(*i==' '){
			v.push_back(w);
			w="";
		}
		else if(i+1==s.end()){
			w+=*i;
			v.push_back(w);
		}
		else
			w+=*i;
	}
	return v;
}
