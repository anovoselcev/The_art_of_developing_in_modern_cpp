#include <string>
#include "test_runner.h"
#include "profile.h"
#include<array>
#include<list>
using namespace std;

class Editor {
public:
  Editor()
    : pos(text.end()) {
  }

  void Left() {
    pos = Advance(pos, -1);
  }

  void Right() {
    pos = Advance(pos, 1);
  }

  void Insert(char token) {
    text.insert(pos, token);
  }

  void Cut(size_t tokens = 1) {
    auto pos2 = Advance(pos, tokens);
    buffer.assign(pos, pos2);
    pos = text.erase(pos, pos2);
  }

  void Copy(size_t tokens = 1) {
    auto pos2 = Advance(pos, tokens);
    buffer.assign(pos, pos2);
  }

  void Paste() {
    text.insert(pos, buffer.begin(), buffer.end());
  }

  string GetText() const {
    return {text.begin(), text.end()};
  }
  char GetCursor(){
	  return *pos;
  }
private:
  using Iterator = list<char>::iterator;
  list<char> text;
  list<char> buffer;
  Iterator pos;

  Iterator Advance(Iterator it, int steps) const {
    while (steps > 0 && it != text.end()) {
      ++it;
      --steps;
    }
    while (steps < 0 && it != text.begin()) {
      --it;
      ++steps;
    }
    return it;
  }
};

void TypeText(Editor& editor, const string& text) {
  for(char c : text) {
    editor.Insert(c);
  }
}

void TestEditing() {
  {
	LOG_DURATION("EDITING");
    Editor editor;

    const size_t text_len = 12;
    const size_t first_part_len = 7;
    TypeText(editor, "hello, world");
    for(size_t i = 0; i < text_len; ++i) {
      editor.Left();
    }
    editor.Cut(first_part_len);
    for(size_t i = 0; i < text_len - first_part_len; ++i) {
      editor.Right();
    }
    TypeText(editor, ", ");
    editor.Paste();
    editor.Left();
    editor.Left();
    editor.Cut(3);

    ASSERT_EQUAL(editor.GetText(), "world, hello");
  }
  {
    Editor editor;

    TypeText(editor, "misprnit");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Cut(1);
    editor.Right();
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "misprint");
  }
}

void TestReverse() {
	LOG_DURATION("REVERSE");
  Editor editor;

  const string text = "esreveR";
  for(char c : text) {
    editor.Insert(c);
    editor.Left();
  }

  ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
	LOG_DURATION("NOTEXT");
  Editor editor;
  ASSERT_EQUAL(editor.GetText(), "");
  editor.Left();
  editor.Left();
  editor.Right();
  editor.Right();
  editor.Copy(0);
editor.Cut(0);
 editor.Paste();
// cout<<editor.GetText()<<endl;
  ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
	LOG_DURATION("EBUFFER");
  Editor editor;

  editor.Paste();
  TypeText(editor, "example");
  editor.Left();
  editor.Left();
  editor.Paste();
  editor.Right();
  editor.Paste();
  editor.Copy(0);
  editor.Paste();
  editor.Left();
  editor.Cut(0);
  editor.Paste();

  ASSERT_EQUAL(editor.GetText(), "example");
}

void TestTotal(){
	Editor ed;
	TypeText(ed, "hello, world");
	for(int i = 0;i<12;i++)
		ed.Left();
	//cout<<ed.GetCursor()<<endl;
	ed.Cut(12);
	ed.Paste();
	//cout<<ed.GetCursor()<<endl;
	ed.Insert('1');
	ed.Left();
	ed.Cut(2);
	for(int i = 0;i<12;i++)
			ed.Left();
	ed.Cut(1000);
	ASSERT_EQUAL(ed.GetText(),"");
}
void TestCut()
{
	LOG_DURATION("CUT");
	Editor editor;
	//1
	editor.Cut(10);
	editor.Insert('a');
	editor.Left();
	//2
	editor.Cut(1);
	ASSERT_EQUAL(editor.GetText(), "");
	editor.Paste();
	ASSERT_EQUAL(editor.GetText(), "a");
	//3
	editor.Cut(0);
	editor.Paste();
	ASSERT_EQUAL(editor.GetText(), "a");
	TypeText(editor, "bcde");
	editor.Left();editor.Left();editor.Left();editor.Left();editor.Left();
	//4
	editor.Cut(10);
	ASSERT_EQUAL(editor.GetText(), "");
	editor.Paste();
	ASSERT_EQUAL(editor.GetText(), "abcde");
	editor.Left();editor.Left();editor.Left();editor.Left();editor.Left();
	//5
	editor.Cut(5);
	ASSERT_EQUAL(editor.GetText(), "");
	editor.Paste();
	//6
	editor.Left();editor.Left();editor.Left();editor.Left();editor.Left();
	//cout<<editor.GetCursor()<<endl;
	editor.Cut(1);
	//cout<<editor.GetText()<<endl;
	ASSERT_EQUAL(editor.GetText(), "bcde");
	//cout<<editor.GetCursor()<<endl;
	editor.Right();
	//cout<<editor.GetCursor()<<endl;
	//cout<<editor.GetText()<<endl;
	editor.Cut(1);
	//cout<<editor.GetText()<<endl;
	ASSERT_EQUAL(editor.GetText(), "bde");
	editor.Cut(1);
	editor.Cut(1);
	ASSERT_EQUAL(editor.GetText(), "b");
}

void TestCopy()
{
	LOG_DURATION("COPY");
	Editor editor;
	//1
	editor.Copy(10);
	editor.Insert('a');
	editor.Paste();
	editor.Left();
	ASSERT_EQUAL(editor.GetText(), "a");
	//2
	editor.Copy(1);
	editor.Paste();
	ASSERT_EQUAL(editor.GetText(), "aa");//between a
    //3
	editor.Copy(0);
	editor.Paste();
	ASSERT_EQUAL(editor.GetText(), "aa");
	TypeText(editor, "bcde");
	//cout<<editor.GetText()<<endl;
	editor.Left();editor.Left();editor.Left();editor.Left();editor.Left();editor.Left();
	//cout<<editor.GetText()<<endl;
	//4
	//cout<<editor.GetText()<<endl;
	editor.Cut(10);

	ASSERT_EQUAL(editor.GetText(), "");
	//cout<<editor.GetText()<<endl;
	editor.Paste();
	//cout<<editor.GetText()<<endl;
	ASSERT_EQUAL(editor.GetText(), "abcdea");
}
int main() {
	LOG_DURATION("Total time");
  TestRunner tr;
 RUN_TEST(tr, TestEditing);
 RUN_TEST(tr, TestReverse);
 RUN_TEST(tr, TestNoText);
 RUN_TEST(tr, TestEmptyBuffer);
  RUN_TEST(tr, TestCopy);
  RUN_TEST(tr, TestCut);
  RUN_TEST(tr, TestTotal);
  return 0;
}
