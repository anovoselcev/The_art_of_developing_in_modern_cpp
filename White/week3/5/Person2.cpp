#include<map>
#include<string>
#include<vector>
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
  void findfirstpast(int year,string past){
	  int n=maxyear(year);
	  //cout<<n<<" "<<minyear(year)<<endl;
	  //cout<<names[n].first<<" "<<names[year].first<<" "<<names[n].f1<<endl;
	  if((names[n].first!=past)&&(names[n].f1==true)){
		  past=names[n].first;
		 // cout<<"ADD"<<past<<endl;
		  firstpast.push_back(past);
		  if(n!=minyear(year)){
			 // cout<<"go+"<<endl;
		  	  findfirstpast(n,past);
		  }
		  }
		  else {
			 // cout<<"Skip with "<<names[year].first<<endl;
			  if(n!=minyear(year)){
				//  cout<<"go-"<<endl;
				  findfirstpast(n,past);
			  }
		  	  }
		  }
  void findlastpast(int year,string past){
	  int n=maxyear(year);
	 // cout<<n<<" "<<minyear(year)<<endl;
	  if((names[n].last!=past)&&(names[n].f2==true)){
		  past=names[n].last;
		  //cout<<"ADD"<<past<<endl;
		  lastpast.push_back(past);
		  	  if(n!=minyear(year)){
		  		//cout<<"go+"<<endl;
		  	  	  findlastpast(n,past);
		  	  }
	  		  }
	  	 else {
	  		//cout<<"Skip with "<<names[year].last<<endl;
	  		if(n!=minyear(year)){
	  			//cout<<"go-"<<endl;
	  			findlastpast(n,past);
	  		}
	  	 }
    }
  string GetFullNameWithHistory(int year){
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

	  		  if(names[year].first.size()==0){
	  			  findlastpast(year,names[year].last);
	  			  string s="";
	  			  if(lastpast.size()>0){
	  				  for(int i=0;i<lastpast.size()-1;i++)
	  					  s+=lastpast[i]+", ";
	  				  s+=lastpast[lastpast.size()-1];
	  				  lastpast.clear();
	  				  return names[year].last+" ("+s+") with unknown first name";
	  			  }
	  			  else
	  				return names[year].last+" with unknown first name";
	  		  }
	  		  else if(names[year].last.size()==0){
	  			findfirstpast(year,names[year].first);
	  			string s="";
	  			if(firstpast.size()>0){
	  				for(int i=0;i<firstpast.size()-1;i++)
	  					s+=firstpast[i]+", ";
	  				s+=firstpast[firstpast.size()-1];
	  				firstpast.clear();
	  				 return names[year].first+" ("+s+") with unknown last name";
	  			}
	  				else
	  				  return names[year].first+" with unknown last name";
	  	  }
	  		  else{
	  			findfirstpast(year,names[year].first);
	  			findlastpast(year,names[year].last);
	  			//cout<<firstpast.size()<<"    "<<lastpast.size()<<endl;
	  			if((lastpast.size()==0)&&(firstpast.size()==0))
	  				return names[year].first+" "+names[year].last;
	  			else if(lastpast.size()==0){
	  				string s="";
	  				for(int i=0;i<firstpast.size()-1;i++)
	  					s+=firstpast[i]+", ";
	  				s+=firstpast[firstpast.size()-1];
	  				firstpast.clear();
	  				return names[year].first+" ("+s+") "+names[year].last;
	  			}
	  			else if(firstpast.size()==0){
	  				string s="";
	  				for(int i=0;i<lastpast.size()-1;i++)
	  					s+=lastpast[i]+", ";
	  				s+=lastpast[lastpast.size()-1];
	  				lastpast.clear();
	  				return names[year].first+" "+names[year].last+" ("+s+")";
	  			}
	  			else{
	  				string s1="",s2="";
	  				for(int i=0;i<lastpast.size()-1;i++)
	  					s2+=lastpast[i]+", ";
	  				s2+=lastpast[lastpast.size()-1];
	  				for(int i=0;i<firstpast.size()-1;i++)
	  					s1+=firstpast[i]+", ";
	  				s1+=firstpast[firstpast.size()-1];
	  				firstpast.clear();
	  				lastpast.clear();
	  				return names[year].first+" ("+s1+") "+names[year].last+" ("+s2+")";
	  			}
  }
	  	  }
  }
private:
  struct name{
	  string first,last;
	  bool f1=false,f2=false;
  };
  map<int,name> names;
  vector<string> firstpast;
  vector<string> lastpast;
};


