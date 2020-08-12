#include<iostream>
#include<map>
#include<set>
#include<sstream>
#include<iomanip>
#include<algorithm>
#include<system_error>
#include<stdexcept>
#include<exception>
#include<fstream>

using namespace std;
class Date{//определим класс дату с конструктором
public:
	int day,month,year;
	Date(int x,int y,int z){//конструктор где кроме создания объекта его элементы проверяются на валидность
		year=x;// не проверяем год на валидность
		if((y<13)&&(y>0))//проверяем месяц на валидность
			month=y;
		else//если не валидно,то кидаем ошибку
			throw runtime_error("Month value is invalid: "+to_string(y));
		if((z>0)&&(z<32))//проверяем день на валидность
			day=z;
		else//если не валиден кидаем ошибку
			throw runtime_error("Day value is invalid: "+to_string(z));
	}
};
bool operator<(const Date& date1,const Date& date2){ //Для сортировки по датам
	if(date1.year<date2.year)
		return true;
	if(date1.year>date2.year)
		return false;
	if(date1.month<date2.month)
		return true;
	if(date1.month>date2.month)
		return false;
	else
		return date1.day<date2.day;
}
class Events{
public:
	void Addevent(const Date& date,const string& event){//метод добавления нового события
		events[date].insert(event);
	}
	bool Deletevent(const Date& date,const string &event){//метод для удаления конкретного события
		if(events.count(date)==0)//если там пусто, то ничего не найдено
			return false;
		else if(events[date].count(event)==0)//если за эту дату таких событий нет, то не найдено
			return false;
		else{//если нашли удаляем
			events[date].erase(event);
			return true;
		}
	}
	int Deletevents(const Date &date){//метод для удаления событий в определенную дату
		int n=events[date].size();//смотрим сколько событий
		events.erase(date);
		return n;
		//выводим что получилось
	}
	const void Findevents(const Date& date){
		if(events.count(date)!=0){//если ничего нет, то вроде по условию ничего не пишем
			for(const auto&x:events[date]){// если что-то есть выведем это
				cout<<x<<endl;
			}
		}
	}
	const void Printevents(){//выведем все что есть
		for(const auto&x:events){
			for(const auto&y:x.second){
				cout<<setw(4) << setfill('0')<<x.first.year<<"-"<<setw(2) << setfill('0')<<x.first.month<<"-"<<setw(2) << setfill('0')<<x.first.day<<" "<<y<<endl;
			}
		}
	}

private:
	map<Date,set<string>> events;
};

Date CorrectDate(stringstream &stream,string s){//проверяем корректность формата даты
	stringstream wrong;
	wrong << "Wrong date format: " << s;
	stringstream newstream(s);
	string end;
	int x,y,z;//год месяц день
	char s1,s2;
	newstream>>x>>s1>>y>>s2>>z;
	//cout<<newstream.peek()<<" "<<char(newstream.peek())<<endl;
	if((newstream)&&(s1=='-')&&(s2=='-')&&(newstream.peek()==-1))
		return Date(x,y,z);
	else
		throw runtime_error(wrong.str());
}

int main() {
	Events a;
	string command;
	while (getline(cin, command)){
		stringstream stream(command);//меняем поток на stringstream
		string cmd,sub;
		try{//запускаем блок с исключением
			getline(stream,cmd,' ');//считаем команду
			//cout<<cmd<<endl;
			if(cmd=="Add"){
				stream>>sub;
				Date date=CorrectDate(stream,sub);//отсюда проверяем формат даты и ее валидность в случае успеха идем дальше,нет ловим исключение
				string event;
				stream>>event;
				if(!event.empty())
					a.Addevent(date,event);//добавляем событие

			}
			else if(cmd=="Del"){
				stream>>sub;//отсюда проверяем формат даты и ее валидность в случае успеха идем дальше,нет ловим исключение
				Date date=CorrectDate(stream,sub);
				string event;
				stream>>event;
				if(event.empty()){//если после даты ничего нет то удаляем по дате
					cout<<"Deleted "<<a.Deletevents(date)<<" events"<<endl;;
				}
				else{//если же дано еще и событие ,то удаляем по дате и событию
					if(a.Deletevent(date,event))
						cout<<"Deleted successfully"<<endl;
					else
						cout<<"Event not found"<<endl;
				}
			}
			else if(cmd=="Print")
				a.Printevents();//выводи все что есть
			else if(cmd=="Find"){
				stream>>sub;
				Date date=CorrectDate(stream,sub);//отсюда проверяем формат даты и ее валидность в случае успеха идем дальше,нет ловим исключение
				a.Findevents(date);
			}
			else if(!cmd.empty()){//если не поймали ни одну команду и это не пустая строка
				cout<<"Unknown command: "<<cmd<<endl;//это неизвестная команда выводим ее, завершаем программу
				break;
			}
		}
		catch(runtime_error&f){
			cout << f.what()<<endl;//ловим исключение,пишем проблему,завершаем программу
			break;
		}
	}
	return 0;
}
