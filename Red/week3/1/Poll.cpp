#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
#include<deque>
#include<iterator>
using namespace std;

template <class T>
class ObjectPool {
public:
  T* Allocate(){
	  if(close.size() == 0){
		  auto it = open.insert(new T);
		  return *it.first;
	  }
	  else{
		 auto it = open.insert(close.front());
		  //delete close.front();
		  close.pop_front();
		 return *it.first;
	  }
  }
  T* TryAllocate(){
	  if(close.size() == 0){
		  return nullptr;
	 	  }
	 else{
	 	auto it = open.insert(close.front());
	 	//delete 	close.front();;
	 	close.pop_front();
	 	return *it.first;
	 }
  }

  void Deallocate(T* object){
	  auto it = open.find(object);
	  if(it == end(open))
		  throw invalid_argument("");
	  else{
		  close.push_back(*it);
		  //delete *it;
		  open.erase(it);
	  }
  }

  ~ObjectPool(){
	  while(open.size()!=0){
		  delete *begin(open);
		  open.erase(open.begin());
	  }
	  while(close.size()!=0){
	  		  delete *begin(close);
	  		  close.pop_front();
	  	  }
  }

private:
  set<T*> open;
  deque<T*> close;
};

void TestObjectPool() {
  ObjectPool<string> pool;
  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();
  *p1 = "first";
  *p2 = "second";
  *p3 = "third";
  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");
  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);
  return 0;
}
