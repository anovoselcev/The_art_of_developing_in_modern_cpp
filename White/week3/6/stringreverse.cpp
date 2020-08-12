class ReversibleString{
	public:
	ReversibleString(){
			str="";
		}
	ReversibleString(const string& s){
		str=s;
	}
	void Reverse(){
		for(int i=0;i<str.size()/2;i++)
			swap(str[i],str[str.size()-1-i]);
	}
	string ToString() const{
		return str;
	}
	private:
	string str;

};
