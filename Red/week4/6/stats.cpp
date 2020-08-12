#include"stats.h"
Stats::Stats(){
	ms["GET"] = 0;
	ms["POST"] = 0;
	ms["PUT"] = 0;
	ms["DELETE"] = 0;
	ms["UNKNOWN"] = 0;
	us["/"] = 0;
	us["/order"] = 0;
	us["/product"] = 0;
	us["/basket"] = 0;
	us["/help"] = 0;
	us["unknown"] = 0;
}
void Stats::AddMethod(string_view method){
	if((method != "GET")&&(method != "POST")&&(method != "PUT")&&(method != "DELETE"))
		method = "UNKNOWN";
	ms[method]++;
}
void Stats::AddUri(string_view uri){
	if((uri != "/")&&(uri != "/order")&&(uri != "/product")&&(uri != "/basket")&&(uri != "/help"))
		uri = "unknown";
	us[uri]++;
}
const map<string_view, int>& Stats::GetMethodStats() const{
	return ms;
}
const map<string_view, int>& Stats::GetUriStats() const{
	return us;
}

HttpRequest ParseRequest(string_view line){
	HttpRequest hr;
	while(line[0]==' ')
		line.remove_prefix(1);
	size_t space = line.find(' ');
	hr.method = line.substr(0,space);
	line.remove_prefix(space+1);
	space = line.find(' ');
	hr.uri = line.substr(0,space);
	line.remove_prefix(space+1);
	hr.protocol = line.substr(0,line.npos);
	//cout<<"Method = "<<hr.method<<"  URI = "<<hr.uri<<"  Protocol = "<<hr.protocol<<endl;
	return hr;
}
