#include <iostream>
#include<cmath>
#include<memory>
#include<sstream>
#include<vector>
#include <iomanip>
using namespace std;

class Figure{
public:
	Figure(const string& name):_name(name){}
	virtual string Name() const =0;
	virtual double Perimeter() const =0;
	virtual double Area() const =0;
	const string _name;
};

class Triangle:public Figure{
public:
	Triangle(const string&name,double a,double b,double c):Figure(name){
		_a=a;
		_b=b;
		_c=c;
	}
	string Name() const  override{return _name;}
	double Perimeter() const{return _a+_b+_c;}
	double Area() const {return sqrt(Perimeter()/2*(Perimeter()/2-_a)*(Perimeter()/2-_b)*(Perimeter()/2-_c));}
private:
	double _a,_b,_c;
};

class Rect:public Figure{
public:
	Rect(const string&name,double width,double height):Figure(name){
		_width=width;
		_height=height;
	}
	string Name() const  override{return _name;}
	double Perimeter() const{return 2*(_width+_height);}
	double Area() const {return _width*_height;}
private:
	double _width,_height;
};

class Circle:public Figure{
public:
	Circle(const string&name,double r):Figure(name){
		_r=r;
	}
	string Name() const  override{return _name;}
	double Perimeter() const{return 2*3.14*_r;}
	double Area() const {return 3.14*_r*_r;}
private:
	double _r;
};

shared_ptr<Figure> CreateFigure(istream& stream){
	shared_ptr<Figure> F;
	string name;
	stream>>name;
	if(name=="RECT"){
		double w,h;
		stream>>w>>h;
		F = make_shared<Rect>(name,w,h);
	}
	else if(name=="TRIANGLE"){
		double a,b,c;
		stream>>a>>b>>c;
		F = make_shared<Triangle>(name,a,b,c);
	}
	else if(name=="CIRCLE"){
		double r;
		stream>>r;
		F = make_shared<Circle>(name,r);
		}
	return F;
}

int main() {
  vector<shared_ptr<Figure>> figures;
  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "ADD") {
      figures.push_back(CreateFigure(is));
    } else if (command == "PRINT") {
      for (const auto& current_figure : figures) {
        cout << fixed << setprecision(3)
             << current_figure->Name() << " "
             << current_figure->Perimeter() << " "
             << current_figure->Area() << endl;
      }
    }
  }
  return 0;
}
