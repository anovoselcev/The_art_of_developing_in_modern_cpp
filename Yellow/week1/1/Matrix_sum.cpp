#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

class Matrix{
public:
	void CheckRange(int a, int b) const {
	  if ((a < 0) or (a >= num_rows)) {
	      throw std::out_of_range("...");
	  }
	  if ((b < 0) or (b >= num_cols)) {
	      throw std::out_of_range("...");
	  }
	}
	Matrix(){
		matrix.resize(0);
		num_rows=0;
		num_cols=0;
	}
	Matrix(int a,int b){
		Reset(a,b);
	}
	void Reset(int a,int b){
		if(a<0)
			throw out_of_range("num_rows must be >= 0");
		if(b<0)
			throw out_of_range("num_columns must be >= 0");
		if(a==0 || b==0)
			a=b=0;
		num_rows=a;
		num_cols=b;
		matrix.resize(num_rows);
		for(int i=0;i<matrix.size();i++)
			matrix[i].resize(num_cols);
		for(int i=0;i<matrix.size();i++){
			for(int j=0;j<matrix[i].size();j++)
				matrix[i][j]=0;
	}
	}
	int At(int a,int b) const {CheckRange(a,b); return matrix[a][b];}
	int& At(int a,int b){CheckRange(a,b);return matrix[a][b];}
	int GetNumRows() const {return num_rows;}
	int GetNumColumns() const {return num_cols;}
private:
	int num_rows,num_cols;
	vector<vector<int>> matrix;
};

istream& operator>>(istream& stream,Matrix& m){
	int a,b;
	stream>>a>>b;
	m=Matrix(a,b);
	for(int i=0;i<m.GetNumRows();i++){
		for(int j=0;j<m.GetNumColumns();j++)
			stream>>m.At(i,j);
	}
	return stream;
}
ostream& operator<<(ostream& stream, const Matrix&m){
	stream<<m.GetNumRows()<<" "<<m.GetNumColumns()<<endl;
	for(int i=0;i<m.GetNumRows();i++){
		for(int j=0;j<m.GetNumColumns();j++){
			if(j!=m.GetNumColumns()-1)
				stream<<m.At(i,j)<<" ";
			else
				stream<<m.At(i,j);
		}
		stream<<endl;
	}
	return stream;
}
bool operator==(const Matrix&m1,const Matrix&m2){
	if((m1.GetNumColumns()!=m2.GetNumColumns())||(m1.GetNumRows()!=m2.GetNumRows()))
		return false;
	else{
		for(int i=0;i<m1.GetNumRows();i++){
			for(int j=0;j<m1.GetNumColumns();j++){
				if(m1.At(i,j)!=m2.At(i,j))
					return false;
			}
		}
	}
	return true;
}
Matrix operator+(const Matrix&m1,const Matrix&m2){
	Matrix m;
	if(m1.GetNumRows()!=m2.GetNumRows())
		throw invalid_argument("Mismatched number of rows");
	if (m1.GetNumColumns()!=m2.GetNumColumns())
		throw invalid_argument("Mismatched number of columns");
	else if(m1.GetNumRows()!=0||m1.GetNumColumns()!=0){
		m=Matrix(m1.GetNumRows(),m1.GetNumColumns());
		for(int i=0;i<m1.GetNumRows();i++){
			for(int j=0;j<m1.GetNumColumns();j++)
				m.At(i,j)=m1.At(i,j)+m2.At(i,j);
		}
	}
	return m;
}
