#include "test_runner.h"
#include<vector>
using namespace std;

template<typename Type>
class Table{
public:
	void Resize(size_t w,size_t h){
		_w=w;
		_h=h;
		_table.resize(_w);
		for(auto&x:_table)
			x.resize(_h);
	}
	Table(size_t w,size_t h) : _w(w),_h(h){
		Resize(_w,_h);
	}
	pair<size_t,size_t> Size() const{
		return make_pair(_w,_h);
	}
	vector<Type>& operator[](const int i)   {
		return _table.at(i);
	}
	vector<Type>& operator[](const int i) const   {
			return _table.at(i);
		}
private:
	size_t _w,_h;
	vector<vector<Type>> _table;


};

void TestTable() {
  Table<int> t(1, 1);
  ASSERT_EQUAL(t.Size().first, 1u);
  ASSERT_EQUAL(t.Size().second, 1u);
 t[0][0] = 42;
 ASSERT_EQUAL(t[0][0], 42);
 t.Resize(3, 4);
 ASSERT_EQUAL(t.Size().first, 3u);
 ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestTable);
  return 0;
}
