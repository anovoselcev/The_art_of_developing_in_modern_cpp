#include <iostream>
#include<algorithm>
#include<vector>
#include<iterator>
using namespace std;

ostream& operator<<(ostream& stream,const vector<int>& v){
	for(auto a=v.begin();a!=v.end();a++){
		if(a+1!=v.end())
			stream<<*a<<" ";
		else
			stream<<*a;
	}
	return stream;
}

int main() {
	int N;
	cin>>N;
	vector<int> v(N);
	for(int i=0;i<N;i++)
		v[i]=i+1;
	reverse(v.begin(),v.end());
	do{
		cout<<v<<endl;
	}while(prev_permutation(v.begin(),v.end()));
	return 0;
}
