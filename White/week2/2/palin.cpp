bool IsPalindrom(string s){
	bool f=true;
	for(int i=0;i<s.size()/2;i++){
		if(s[i]!=s[s.size()-1-i])
			f=false;
	}
	return f;
}
