#include <iostream>
#include<vector>
#include"test_runner.h"
using namespace std;

template<typename Type>

class Deque{
public:
	Deque(){}
	bool Empty() const {
		return _front.empty()&&_back.empty();
	}
	size_t Size() const {
		return _front.size()+_back.size();
	}
	Type& At(const size_t i){
		if(i<_front.size())
			return _front.at(_front.size()-i-1);
		else if(i-_front.size()<_back.size())
			return _back.at(i-_front.size());
		else
			throw out_of_range("");
	}
	const Type& At(const size_t i) const{
		if(i<_front.size())
			return _front.at(_front.size()-i-1);
		else if(i-_front.size()<_back.size())
			return _back.at(i-_front.size());
		else
			throw out_of_range("");
		}
	Type& operator[](const size_t i){
		return At(i);
	}
	const Type& operator[](const size_t i) const{
		return At(i);
	}
	const Type& Front() const{
		if(_front.size()!=0)
			return _front.back();
		else
			return _back.front();
	}

	Type& Front() {
		if(_front.size()!=0)
			return _front.back();
		else
			return _back.front();
	}
	const Type& Back() const {
		if(_back.size()!=0)
			return _back.back();
		else
			return _front.front();
	}
	Type& Back(){
		if(_back.size()!=0)
			return _back.back();
		else
			return _front.front();
	}
	void PushFront(const Type& elem){
		_front.push_back(elem);
	}
	void PushBack(const Type& elem){
		_back.push_back(elem);
	}

private:
	vector<Type> _front;
	vector<Type> _back;
};
void TestEmpty() {
  Deque<int> dq;
  ASSERT(dq.Empty());
}

void TestPush() {
  Deque<int> dq;
  dq.PushBack(2);
  dq.PushFront(1);
  ASSERT(!dq.Empty());
}

void TestSize() {
  Deque<int> dq;
  dq.PushBack(2);
  dq.PushFront(1);
  ASSERT_EQUAL(dq.Size(), 2u);
}

void TestFront() {
  Deque<int> dq;
  dq.PushFront(1);
  ASSERT_EQUAL(dq.Front(), 1);

  dq.Front() = 0;
  ASSERT_EQUAL(dq.Front(), 0);
}

void TestBack() {
  Deque<int> dq;
  dq.PushBack(1);
  ASSERT_EQUAL(dq.Back(), 1);

  dq.Back() = 0;
  ASSERT_EQUAL(dq.Back(), 0);
}

void TestOperator() {
  // front и back имеют элементы
  Deque<int> dq_of_int;
  dq_of_int.PushFront(1);
  dq_of_int.PushFront(2);
  dq_of_int.PushFront(3);
  dq_of_int.PushBack(4);
  dq_of_int.PushBack(5);
  ASSERT_EQUAL(dq_of_int[0], 3);
  ASSERT_EQUAL(dq_of_int[1], 2);
  ASSERT_EQUAL(dq_of_int[2], 1);
  ASSERT_EQUAL(dq_of_int[3], 4);
  ASSERT_EQUAL(dq_of_int[4], 5);

  // front имеет элементы, back – пуст
  Deque<double> dq_of_db;
  dq_of_db.PushFront(1.5);
  dq_of_db.PushFront(2.5);
  dq_of_db.PushFront(3.5);
  ASSERT_EQUAL(dq_of_db[0], 3.5);
  ASSERT_EQUAL(dq_of_db[1], 2.5);
  ASSERT_EQUAL(dq_of_db[2], 1.5);

  // back имеет элементы, front – пуст
  Deque<char> dq_of_ch;
  dq_of_ch.PushBack('a');
  dq_of_ch.PushBack('b');
  ASSERT_EQUAL(dq_of_ch[0], 'a');
}

void TestAt() {
  // front и back имеют элементы
  Deque<int> dq_of_int;
  dq_of_int.PushFront(1);
  dq_of_int.PushFront(2);
  dq_of_int.PushFront(3);
  dq_of_int.PushBack(4);
  dq_of_int.PushBack(5);
  ASSERT_EQUAL(dq_of_int.At(0), 3);
  ASSERT_EQUAL(dq_of_int.At(1), 2);
  ASSERT_EQUAL(dq_of_int.At(2), 1);
  ASSERT_EQUAL(dq_of_int.At(3), 4);
  ASSERT_EQUAL(dq_of_int.At(4), 5);

  // front имеет элементы, back – пуст
  Deque<double> dq_of_db;
  dq_of_db.PushFront(1.5);
  dq_of_db.PushFront(2.5);
  dq_of_db.PushFront(3.5);
  ASSERT_EQUAL(dq_of_db.At(0), 3.5);
  ASSERT_EQUAL(dq_of_db.At(1), 2.5);
  ASSERT_EQUAL(dq_of_db.At(2), 1.5);

  try {
    dq_of_db.At(3);
  } catch (const out_of_range& ex) {
    bool exception_caught = true;
    ASSERT(exception_caught);
  }

  // back имеет элементы, front – пуст
  Deque<char> dq_of_ch;
  dq_of_ch.PushBack('a');
  dq_of_ch.PushBack('b');
  ASSERT_EQUAL(dq_of_ch.At(0), 'a');
}
int main() {
  TestRunner tr;
  RUN_TEST(tr, TestEmpty);
  RUN_TEST(tr, TestPush);
  RUN_TEST(tr, TestSize);
  RUN_TEST(tr, TestFront);
  RUN_TEST(tr, TestBack);
  RUN_TEST(tr, TestOperator);
  RUN_TEST(tr, TestAt);
  return 0;
}
