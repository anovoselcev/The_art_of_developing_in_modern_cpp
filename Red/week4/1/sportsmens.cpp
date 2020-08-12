#include <iostream>
#include<list>
#include<deque>
#include<algorithm>
using namespace std;

int main() {
	int n,num,que;
	list<int> sport;
	deque<list<int>::iterator> pos;
	pos.assign(100000,end(sport));
	cin>>n;
	for(int i = 0;i<n;i++){
		cin>>num>>que;
		pos[num]=sport.insert(pos[que],num);
	}
	for(const auto&x:sport)
		cout<<x<<' ';
	return 0;
}
