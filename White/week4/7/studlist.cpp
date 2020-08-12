#include <iostream>
#include<fstream>
#include<vector>
using namespace std;

struct Student{
	string name,surname;
	int day,month,year;
};


int main() {
	int n;
	cin>>n;
	vector<Student> v(n);
	for(int i=0;i<n;i++)
		cin>>v[i].name>>v[i].surname>>v[i].day>>v[i].month>>v[i].year;
	cin>>n;
	for(int i=0;i<n;i++){
		string s;
		int k;
		cin>>s>>k;
		if((s=="name")&&(k<=v.size())&&(k>0))
			cout<<v[k-1].name<<" "<<v[k-1].surname<<endl;
		else if((s=="date")&&(k<=v.size())&&(k>0))
			cout<<v[k-1].day<<"."<<v[k-1].month<<"."<<v[k-1].year<<endl;
		else
			cout<<"bad request"<<endl;
	}
	return 0;
}
