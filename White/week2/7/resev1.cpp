vector<int> Reversed(const vector<int>& v){
	vector<int> a=v;
	for(int i=0;i<a.size()/2;i++)
		swap(a[i],a[a.size()-1-i]);
	return a;
}
