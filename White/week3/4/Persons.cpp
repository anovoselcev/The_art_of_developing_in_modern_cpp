#include<map>
class Person {
public:
	int minyear(int year){
		int min=year;
		for(auto x:names){
			if(x.first<min)
				min=x.first;
		}
		return min;
	}
	int maxyear(int year){
		int max=minyear(year);
		for(auto x: names){
			if((x.first>max)&&(x.first<year))
				max=x.first;
		}
		return max;
	}
	void findfirst(int year){
		if(names[year].f2==false){
			int n=maxyear(year);
			while((n>minyear(year))&&((names[n].f2==false)||(names[n].last.size()==0)))
				n=maxyear(n);
			names[year].last=names[n].last;
		}
	}
	void findlast(int year){
		if(names[year].f1==false){
			int n=maxyear(year);
			while((n>minyear(year))&&((names[n].f1==false)||(names[n].first.size()==0)))
				n=maxyear(n);
			names[year].first=names[n].first;
		}
	}
	void ChangeFirstName(int year, const string& first_name) {
		names[year].first=first_name;
		names[year].f1=true;
		findfirst(year);
	}
	void ChangeLastName(int year, const string& last_name) {
		names[year].last=last_name;
		names[year].f2=true;
		findlast(year);
	}
  string GetFullName(int year) {
	  if(names.size()==0)
		  return "Incognito";
	  else{
		  int min=minyear(year);
		  if((min==year)&&(names[min].first.size()==0)&&(names[min].last.size()==0)){
			  names.erase(min);
			  return "Incognito";
	  }
		  findlast(year);
		  findfirst(year);

		  if(names[year].first.size()==0)
			  return names[year].last+" with unknown first name";
		  else if(names[year].last.size()==0)
		  			  return names[year].first+" with unknown last name";
		  else
			  return names[year].first+" "+names[year].last;
	  }
  }
private:
  struct name{
	  string first,last;
	  bool f1=false,f2=false;
  };
  map<int,name> names;
};

