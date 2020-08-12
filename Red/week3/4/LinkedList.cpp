#include "test_runner.h"

#include <vector>
using namespace std;

template <typename T>
class LinkedList {
public:
  struct Node {
    T value;
    Node* next = nullptr;
  };

  ~LinkedList(){
	  Node* n;
	  while(head!=nullptr){
		  n = head;
		  head = n->next;
		  delete[] n;
	  }
}
  void PushFront(const T& value){
	  if(head == nullptr){
		  head = new Node[1];
		  head[0].value = value;
		  return;
	  }
	  else{
		  Node* n = new Node[1];
		  n->value=value;
		  n->next=head;
		  head = n;
		  return;
	  }
  }
  void InsertAfter(Node* node, const T& value){
	  if(node == nullptr){
		  PushFront(value);
		  return;
	  }
	  else{
		 Node* nnode = new Node[1];
		 Node* ptr = node->next;
		 nnode->value = value;
		 nnode->next = ptr;
		 node->next = nnode;
		 return;
	  }
  }
  void RemoveAfter(Node* node){
	  if(node == nullptr){
		  PopFront();
		  return;
	  }
	  else{
		  Node* dnode = node->next;
		  if(dnode!=nullptr){
			  Node* after = dnode->next;
			  node->next = after;
			  delete[] dnode;
			  return;
		  }
	  }
  }
  void PopFront(){
	  if(head != nullptr){
		  Node* first = head;
		  head = first->next;
		  delete[] first;
		  return;
	  }
  }
  Node* GetHead() { return head; }
  const Node* GetHead() const { return head; }

private:
  Node* head = nullptr;
};

template <typename T>
vector<T> ToVector(const LinkedList<T>& list) {
  vector<T> result;
  for (auto node = list.GetHead(); node; node = node->next) {
    result.push_back(node->value);
  }
  return result;
}

void TestPushFront() {
  LinkedList<int> list;

  	list.PushFront(1);
  	ASSERT_EQUAL(list.GetHead()->value, 1);
  	list.PushFront(2);
  	ASSERT_EQUAL(list.GetHead()->value, 2);
  	list.PushFront(3);
  	ASSERT_EQUAL(list.GetHead()->value, 3);
  	const vector<int> expected = {3, 2, 1};
  	ASSERT_EQUAL(ToVector(list), expected);
}

void TestInsertAfter() {
  LinkedList<string> list;

  list.PushFront("a");
  auto head = list.GetHead();
  ASSERT(head);
  ASSERT_EQUAL(head->value, "a");
//
  list.InsertAfter(head, "b");
  const vector<string> expected1 = {"a", "b"};
  ASSERT_EQUAL(ToVector(list), expected1);

  list.InsertAfter(head, "c");
  const vector<string> expected2 = {"a", "c", "b"};
  ASSERT_EQUAL(ToVector(list), expected2);
}

void TestRemoveAfter() {
  LinkedList<int> list;
  for (int i = 1; i <= 5; ++i) {
    list.PushFront(i);
  }

  const vector<int> expected = {5, 4, 3, 2, 1};
  ASSERT_EQUAL(ToVector(list), expected);

  auto next_to_head = list.GetHead()->next;
  list.RemoveAfter(next_to_head); // СѓРґР°Р»СЏРµРј 3
  list.RemoveAfter(next_to_head); // СѓРґР°Р»СЏРµРј 2

  const vector<int> expected1 = {5, 4, 1};
  ASSERT_EQUAL(ToVector(list), expected1);

  while (list.GetHead()->next) {
    list.RemoveAfter(list.GetHead());
  }
  ASSERT_EQUAL(list.GetHead()->value, 5);
}

void TestPopFront() {
  LinkedList<int> list;

  for (int i = 1; i <= 5; ++i) {
    list.PushFront(i);
  }
  for (int i = 1; i <= 5; ++i) {
    list.PopFront();
  }
  list.PopFront();
  ASSERT(list.GetHead() == nullptr);
}

void TestTop(){
	LinkedList<float>  l;
	l.InsertAfter(l.GetHead(),1);
	ASSERT(l.GetHead()->value == 1);
	l.PopFront();
	ASSERT(l.GetHead() == nullptr);
	l.PushFront(22);
	l.RemoveAfter(l.GetHead());
	ASSERT(l.GetHead()->value == 22);
	ASSERT(l.GetHead()->next == nullptr);
	l.PushFront(22);
	l.PopFront();
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestPushFront);
  RUN_TEST(tr, TestInsertAfter);
  RUN_TEST(tr, TestRemoveAfter);
  RUN_TEST(tr, TestPopFront);
  RUN_TEST(tr,TestTop);
  return 0;
}
