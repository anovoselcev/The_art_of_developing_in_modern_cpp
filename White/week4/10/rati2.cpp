#include <iostream>
#include<cmath>
#include<map>
#include<set>
#include<vector>
#include <exception>
using namespace std;
class Rational {
public:
	int nod(int a,int b){
		a=abs(a);b=abs(b);
		if(a>b)
			swap(b,a);
		while(b%a!=0){
			b=b%a;
			swap(b,a);
		}
		return a;
	}
  Rational(){
	  numerator=0;
	  denominator=1;
  }
  Rational(int numerator0, int denominator0){
	  if((numerator0<0)&&(denominator0<0)){
		  numerator=-numerator0/nod(numerator0,denominator0);
		  denominator=-denominator0/nod(numerator0,denominator0);
	  }
	  else if((denominator0<0)&&(numerator0>0)){
		  numerator=-numerator0/nod(numerator0,denominator0);
		  denominator=-denominator0/nod(numerator0,denominator0);
	  }
	  else if(denominator0==0)
		  throw invalid_argument("invalid_argument");
	  else if((numerator0==0)&&(denominator0!=0)){
		  numerator=0;
		  denominator=1;
	  }
	  else{
		  numerator=numerator0/nod(numerator0,denominator0);
		  denominator=denominator0/nod(numerator0,denominator0);
	  }
  }

  int Numerator() const{
	  return numerator;
  }
  int Denominator() const{
	  return denominator;
  }
private:
  int numerator,denominator;
};

Rational operator+(const Rational&r1,const Rational&r2){
	Rational r(r1.Numerator()*r2.Denominator()+r2.Numerator()*r1.Denominator(),r1.Denominator()*r2.Denominator());
	return r;
}
Rational operator-(const Rational&r1,const Rational&r2){
	Rational r(r1.Numerator()*r2.Denominator()-r2.Numerator()*r1.Denominator(),r1.Denominator()*r2.Denominator());
	return r;
}
bool operator==(const Rational&r1,const Rational&r2){
	if((r1.Numerator()==r2.Numerator())&&(r1.Denominator()==r2.Denominator()))
		return true;
	else
		return false;
}
Rational operator*(const Rational&r1,const Rational&r2){
	Rational r(r1.Numerator()*r2.Numerator(),r1.Denominator()*r2.Denominator());
	return r;
}
Rational operator/(const Rational&r1,const Rational&r2){
	if(r2.Numerator()==0)
		throw domain_error("domain_error");
	else{
		Rational r(r1.Numerator()*r2.Denominator(),r1.Denominator()*r2.Numerator());
		return r;
	}
}
istream& operator>>(istream& stream,Rational&r){
	int a,b;
	stream>>a;
	stream.ignore(1);
	stream>>b;
	if(stream)
		r=Rational(a,b);
	return stream;
}
ostream& operator<<(ostream& stream, const Rational&r){
	stream<<r.Numerator()<<"/"<<r.Denominator();
	return stream;
}
bool operator<(const Rational&r1,const Rational&r2){
	return r1.Numerator()*r2.Denominator()<r1.Denominator()*r2.Numerator();
}
