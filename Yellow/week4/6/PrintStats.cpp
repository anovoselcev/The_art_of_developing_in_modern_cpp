#include <iostream>
#include<vector>
#include<algorithm>
using namespace std;

void PrintStats(vector<Person> persons){
	cout<<"Median age = "<<ComputeMedianAge(begin(persons),end(persons))<<endl;
	auto itG=partition(persons.begin(), persons.end(), [](const Person& p) {
	        return p.gender == Gender::FEMALE;
	    });
	cout<<"Median age for females = "<<ComputeMedianAge(begin(persons),itG)<<endl;
	cout<<"Median age for males = "<<ComputeMedianAge(itG,end(persons))<<endl;
	auto itGF=partition(persons.begin(), itG, [](const Person& p) {
		        return p.is_employed;
		    });
	cout<<"Median age for employed females = "<<ComputeMedianAge(begin(persons),itGF)<<endl;
	cout<<"Median age for unemployed females = "<<ComputeMedianAge(itGF,itG)<<endl;
	auto itGM=partition(itG, end(persons), [](const Person& p) {
			        return p.is_employed;
			    });
	cout<<"Median age for employed males = "<<ComputeMedianAge(itG,itGM)<<endl;
	cout<<"Median age for unemployed males = "<<ComputeMedianAge(itGM,end(persons))<<endl;
}
