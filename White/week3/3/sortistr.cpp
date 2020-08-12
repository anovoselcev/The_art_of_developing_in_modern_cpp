class SortedStrings {
public:
  void AddString(const string& s) {
	  v.push_back(s);
  }
  vector<string> GetSortedStrings() {
	  sort(v.begin(),v.end());
	  return v;
  }
private:
  vector<string> v;
};
