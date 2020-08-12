void MoveStrings(vector<string> &sourse ,vector<string> &destination ){
	for(auto i:sourse)
	destination.push_back(i);
	sourse.clear();
}
