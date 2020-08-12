#include <algorithm>
#include <map>
#include <vector>
using namespace std;
vector<string> FindNamesHistory(const map<int, string>& names_by_year,
                                int year) {
  vector<string> names;
  for (const auto& item : names_by_year) {
    if (item.first <= year && (names.empty() || names.back() != item.second)) {
      names.push_back(item.second);
    }
  }
  return names;
}

string BuildJoinedName(vector<string> names) {
  if (names.empty()) {
    return "";
  }
  reverse(begin(names), end(names));
  string joined_name = names[0];
  for (int i = 1; i < names.size(); ++i) {
    if (i == 1) {
      joined_name += " (";
    } else {
      joined_name += ", ";
    }
    joined_name += names[i];
  }
  if (names.size() > 1) {
    joined_name += ")";
  }
  return joined_name;
}
string BuildFullName(const string& first_name, const string& last_name) {
  if (first_name.empty() && last_name.empty()) {
    return "No person";
  } else if (first_name.empty()) {
    return last_name + " with unknown first name";
  } else if (last_name.empty()) {
    return first_name + " with unknown last name";
  } else {
    return first_name + " " + last_name;
  }
}

class Person {
public:
  void ChangeFirstName(int year, const string& first_name) {
	int min=year;
	for(auto x:first_names){
		if(x.first<min)
			min=x.first;
	}
	if(year>=min)
		first_names[year] = first_name;
  }
  void ChangeLastName(int year, const string& last_name) {
	  int min=year;
	  	for(auto x:first_names){
	  		if(x.first<min)
	  			min=x.first;
	  	}
	  	if(year>=min)
    last_names[year] = last_name;
  }

  string GetFullName(int year) const {
    const vector<string> first_names_history = FindFirstNamesHistory(year);
    const vector<string> last_names_history = FindLastNamesHistory(year);
    string first_name;
    string last_name;
    if (!first_names_history.empty()) {
      first_name = first_names_history.back();
    }
    if (!last_names_history.empty()) {
      last_name = last_names_history.back();
    }
    return BuildFullName(first_name, last_name);
  }

  string GetFullNameWithHistory(int year)const {
    const string first_name = BuildJoinedName(FindFirstNamesHistory(year));
    const string last_name = BuildJoinedName(FindLastNamesHistory(year));
    return BuildFullName(first_name, last_name);
  }
  Person(const string&s1,const string&s2,int year){
	  ChangeFirstName(year,s1);
	  ChangeLastName(year,s2);
  }

private:
  vector<string> FindFirstNamesHistory(int year) const {
    return FindNamesHistory(first_names, year);
  }
  vector<string> FindLastNamesHistory(int year) const {
    return FindNamesHistory(last_names, year);
  }

  map<int, string> first_names;
  map<int, string> last_names;
};


int main(){}
