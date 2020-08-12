#include <iomanip>
#include <iostream>
#include<deque>
#include<map>
#include<algorithm>
#include<set>

using namespace std;

class ReadingManager {
public:
  ReadingManager():users_id(MAX_USER_COUNT_+1,false),page_user(1001,0),rating(1001,0),users(0){}

  void Read(int user_id, int page_count) {
	if(users_id[user_id]){
		int p = user_page[user_id];//save last page
		user_page[user_id]=page_count;//upd page for user
		page_user[p]--;//delet last page
		page_user[page_count]++;//upd user for page
	}
	else{
		users++;
		users_id[user_id]=true;
		user_page[user_id]=page_count;
		page_user[page_count]++;
	}
	double n=0;
	for(int i =0;i<1001;i++){
		if(users!=1)
			rating[i]= n/(users-1);
		n+=page_user[i];
	}
  }

  double Cheer(int user_id) const {
	if(users_id[user_id]){
		if(user_page.size()==1)
			return 1;
		return rating[user_page.at(user_id)];
	}
	else
		return 0;
  }

private:

  static const int MAX_USER_COUNT_ = 100'000;
  map<int,int> user_page;
  deque<bool> users_id;
  //map<int,int> page_user;
  deque<int> page_user;
  deque<double> rating;
  //map<int,double> rating;
  double users;
};


int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ReadingManager manager;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) { //Q
    string query_type;
    cin >> query_type;
    int user_id;
    cin >> user_id;

    if (query_type == "READ") {
    	//cout<<"Im read"<<endl;
      int page_count;
      cin >> page_count;
      manager.Read(user_id, page_count);
    } else if (query_type == "CHEER") {
      cout << setprecision(6) << manager.Cheer(user_id) << "\n";
    }
  }

  return 0;
}
