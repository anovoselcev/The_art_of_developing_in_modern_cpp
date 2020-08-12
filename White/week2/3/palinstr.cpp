vector<string> PalindromFilter(vector<string> s,int n){
	vector<string> r;
	for(auto i:s){
		bool f=true;
			for(int j=0;j<i.size()/2;j++){
				if(i[j]!=i[i.size()-1-j])
					f=false;
			}
			if(f==true && i.size()>=n)
				r.push_back(i);
	}
	return r;
}

