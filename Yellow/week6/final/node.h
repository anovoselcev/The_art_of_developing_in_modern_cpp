#pragma once

#include"date.h"
#include<memory>
#include<string>

using namespace std;

enum class LogicalOperation{
	Or,
	And
};

enum class Comparison{
	Less,
	LessOrEqual,
	Greater,
	GreaterOrEqual,
	Equal,
	NotEqual
};

class Node{
public:
	virtual bool Evaluate(Date date,string event)=0;
};

class EmptyNode : public Node{
	bool Evaluate(Date date,string event);
};

class DateComparisonNode : public Node{
public:
	DateComparisonNode(const Comparison& cmp,Date date);
	bool Evaluate(Date date,string event) override;
private:
	Comparison _cmp;
	Date _date;
};

class EventComparisonNode : public Node{
public:
	EventComparisonNode(const Comparison& cmp,std::string event);
	bool Evaluate(Date date,string event) override;
private:
	Comparison _cmp;
	string _event;

};

class LogicalOperationNode : public Node{
public:
	LogicalOperationNode(const LogicalOperation& op ,shared_ptr<Node> node1,shared_ptr<Node> node2);
	bool Evaluate(Date date,string event) override;
private:
	LogicalOperation _op;
	shared_ptr<Node> n1,n2;
};
