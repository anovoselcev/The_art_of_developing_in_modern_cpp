#include"node.h"

LogicalOperationNode::LogicalOperationNode(const LogicalOperation& op
		,shared_ptr<Node> node1,
		shared_ptr<Node> node2):
		_op(op),n1(node1),n2(node2){}

bool LogicalOperationNode::Evaluate(Date date,string event){
	if(_op==LogicalOperation::And)
		return (n1->Evaluate(date,event))&&(n2->Evaluate(date,event));
	else if(_op==LogicalOperation::Or)
		return (n1->Evaluate(date,event))||(n2->Evaluate(date,event));
}

DateComparisonNode::DateComparisonNode(const Comparison& cmp,Date date):
	_cmp(cmp),_date(date){}
bool DateComparisonNode::Evaluate(Date date,string event){
	if(_cmp==Comparison::NotEqual){
		return !(_date==date);
	}
	else if(_cmp==Comparison::Equal){
		return _date==date;
	}
	else if(_cmp==Comparison::Less){
		return !(_date<date||_date==date);
	}
	else if(_cmp==Comparison::LessOrEqual){
		return !(_date<date);
	}
	else if(_cmp==Comparison::Greater){
		return _date<date;
	}
	else if(_cmp==Comparison::GreaterOrEqual){
		return _date<date||_date==date;
	}
}

EventComparisonNode::EventComparisonNode(const Comparison& cmp,std::string event):
	_cmp(cmp),_event(event){}

bool EventComparisonNode::Evaluate(Date date,string event){
	if(_cmp==Comparison::NotEqual){
			return !(_event==event);
		}
		else if(_cmp==Comparison::Equal){
			return _event==event;
		}
		else if(_cmp==Comparison::Less){
			return !((_event<event)||(_event==event));
		}
		else if(_cmp==Comparison::LessOrEqual){
			return !(_event<event);
		}
		else if(_cmp==Comparison::Greater){
			return _event<event;
		}
		else if(_cmp==Comparison::GreaterOrEqual){
			return  _event<event||_event==event;
		}
}
bool EmptyNode::Evaluate(Date date,string event){return true;}
