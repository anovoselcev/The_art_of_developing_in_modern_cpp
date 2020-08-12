#pragma once

#include <memory>
#include <string>

// Базовый класс арифметического выражения
class Expression {
public:
  virtual ~Expression() = default;

  // Вычисляет значение выражения
  virtual int Evaluate() const = 0;

  // Форматирует выражение как строку
  // Каждый узел берётся в скобки, независимо от приоритета
  virtual std::string ToString() const = 0;
};

using ExpressionPtr = std::unique_ptr<Expression>;

class BinExp : public Expression{
protected:
	ExpressionPtr lhs;
	ExpressionPtr rhs;
};

class ValueExp : public Expression{
public:
	ValueExp(int v) : value(v){}

	int Evaluate() const {return value;}

	std::string ToString() const{
		return std::to_string(value);
	}
private:
	int value;
};

class SumExpr : public BinExp{
public:
	SumExpr(ExpressionPtr l, ExpressionPtr r) : lhs(move(l)), rhs(move(r)) {}

	int Evaluate() const {return lhs->Evaluate()+rhs->Evaluate();}

	std::string ToString() const {
		return '('+lhs->ToString()+')'+'+'+'('+rhs->ToString()+')';
	}
private:
	ExpressionPtr lhs,rhs;
};

class ProductExpr : public BinExp{
public:
	ProductExpr(ExpressionPtr l, ExpressionPtr r) : lhs(move(l)), rhs(move(r)) {}

	int Evaluate() const {return lhs->Evaluate()*rhs->Evaluate();}

	std::string ToString() const{
		return '('+lhs->ToString()+')'+'*'+'('+rhs->ToString()+')';
	}
private:
	ExpressionPtr lhs,rhs;
};

// Функции для формирования выражения
ExpressionPtr Value(int value){
	return std::make_unique<ValueExp>(value);
}
ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right){
	return std::make_unique<SumExpr>(move(left),move(right));
}
ExpressionPtr Product(ExpressionPtr left, ExpressionPtr right){
	return std::make_unique<ProductExpr>(move(left),move(right));
}
