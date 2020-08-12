#include"ini.h"

namespace Ini{
	Section& Document::AddSection(string name){
		return _sections[name];
	}

	const Section& Document::GetSection(const string& name) const{
		return _sections.at(name);
	}

	size_t Document::SectionCount() const{
		return _sections.size();
	}

	Document Load(istream& input){
		Document result;
		string s;
		Section* curr_section = nullptr;
		while(getline(input,s)){
			if(s.size()){
				if(s[0] == '['){
					s = s.substr(1,s.size()-2);
					curr_section = &result.AddSection(s);
				}
				else{
					auto space = s.find('=');
					string key = s.substr(0,space);
					string value = s.substr(space+1);
					curr_section->insert({key,value});
				}
			}
		}
		return result;
	}
}
