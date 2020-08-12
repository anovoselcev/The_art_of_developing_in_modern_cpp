#include "test_runner.h"
#include <functional>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <iostream>

using namespace std;


struct Email {
  string from;
  string to;
  string body;
};

inline std::istream& operator>>(std::istream& input, Email& email)
{
	std::string from, to, body;

	std::getline(input, from);
	std::getline(input, to);
	std::getline(input, body);

	email = Email{std::move(from), std::move(to), std::move(body)};

	return input;
}


inline std::ostream& operator<<(std::ostream& output, const Email& email)
{
	output << email.from << '\n';
	output << email.to << '\n';
	output << email.body << '\n';

	return output;
}
class Worker {
public:
  virtual ~Worker() = default;
  virtual void Process(unique_ptr<Email> email) = 0;
  virtual void Run() {
    // только первому worker-у в пайплайне нужно это имплементировать
    throw logic_error("Unimplemented");
  }

protected:
  unique_ptr<Worker> _next = nullptr;
  // реализации должны вызывать PassOn, чтобы передать объект дальше
  // по цепочке обработчиков
  void PassOn(unique_ptr<Email> email) const{
	  if(_next!=nullptr)
		  _next->Process(move(email));
  }

public:
  void SetNext(unique_ptr<Worker> next){
	  if(_next==nullptr)
		  _next = move(next);
	  else
		  _next->SetNext(move(next));
  }
};


class Reader : public Worker {
public:
  // реализуйте класс
	Reader(istream& is) : _is(is){}

	void Run(){
		Email email;
		string s;
		while (_is >> email) {
			emails_.emplace_back(std::make_unique<Email>(std::move(email)));
		}
		for(auto&x:emails_)
			Process(move(x));
	}
	void Process(unique_ptr<Email> email){
		PassOn(move(email));
	}
private:
	istream& _is;
	std::vector<std::unique_ptr<Email>> emails_;
};


class Filter : public Worker {
public:
  using Function = function<bool(const Email&)>;

  Filter(Function f) : _f(move(f)){}

  void Process(unique_ptr<Email> email) override{
	  if(_f(*email))
		  PassOn(move(email));
  }

public:
  const Function _f;
  // реализуйте класс
};


class Copier : public Worker {
public:
	Copier(std::string s) : _s(move(s)) {}
  // реализуйте класс
	void Process(unique_ptr<Email> email){
		if (email->to != _s){
			auto m = make_unique<Email>(Email{email->from,_s,email->body});
			PassOn(move(email));
		    PassOn(move(m));
		}
		else
			PassOn(move(email));
	}
private:
	std::string _s;
};


class Sender : public Worker {
public:
	Sender(ostream& os) : _os(os) {}
	void Process(unique_ptr<Email> email) override{
		_os << *email;
		PassOn(std::move(email));
	}

private:
	ostream& _os;
  // реализуйте класс
};


// реализуйте класс
class PipelineBuilder {
public:
    explicit PipelineBuilder(istream& in) : ptr(make_unique<Reader>(in)) {
    }

    PipelineBuilder& FilterBy(Filter::Function filter) {
        ptr->SetNext(make_unique<Filter>(move(filter)));
        return *this;
    }

    PipelineBuilder& CopyTo(string recipient) {
        ptr->SetNext(make_unique<Copier>(move(recipient)));
        return *this;
    }

    PipelineBuilder& Send(ostream& out) {
        ptr->SetNext(make_unique<Sender>(out));
        return *this;
    }

    unique_ptr<Worker> Build() {
        return move(ptr);
    }

private:
    unique_ptr<Worker> ptr;
};


void TestSanity() {
  string input = (
    "erich@example.com\n"
    "richard@example.com\n"
    "Hello there\n"

    "erich@example.com\n"
    "ralph@example.com\n"
    "Are you sure you pressed the right button?\n"

    "ralph@example.com\n"
    "erich@example.com\n"
    "I do not make mistakes of that kind\n"
  );
  istringstream inStream(input);
  ostringstream outStream;

  PipelineBuilder builder(inStream);
  builder.FilterBy([](const Email& email) {
    return email.from == "erich@example.com";
  });
  builder.CopyTo("richard@example.com");
  builder.Send(outStream);
  auto pipeline = builder.Build();

  pipeline->Run();

  string expectedOutput = (
    "erich@example.com\n"
    "richard@example.com\n"
    "Hello there\n"

    "erich@example.com\n"
    "ralph@example.com\n"
    "Are you sure you pressed the right button?\n"

    "erich@example.com\n"
    "richard@example.com\n"
    "Are you sure you pressed the right button?\n"
  );
  ASSERT_EQUAL(expectedOutput, outStream.str());
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSanity);
  return 0;
}
