set<string> BuildMapValuesSet(const map<int, string>& m) {
	set<string> value;
	for(auto x:m)
		value.insert(x.second);
	return value;
}

