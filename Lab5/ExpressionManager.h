#ifndef EXPRESSIONMANAGER_H
#define EXPRESSIONMANAGER_H

#include"ExpressionManagerInterface.h"
#include<stack>
#include<vector>
#include<sstream>
#include<algorithm>

//Namespace Definitions
using std::string;
using std::ostream;
using std::stack;
using std::vector;

class Expression : public ExpressionManagerInterface
{
private:
	stack<string> inFixs;
	stack<string> postFix;
	stack<string> preFix;
	vector<string> expression;
	const string operators[8] = { "(","[","{","-","+","*","/","%" };
	string inExp;
	int operNum = 0;
	int start = 0;
	int finish = 0;

public:
	Expression() {};
	Expression(string line) : inExp(line) {};

/**
Returns 1 if it is an op, and 0 if it is not
Works like boolean; std booleans not working right now
*/
	int isOp(string value);
	/**
Returns true if the operands = operators + 1
*/
	bool isoperbal();
/**
Returns true if there is a parentheses match throughout the expression
Also, changes operNum, which stands for the number of operations
*/
	bool isParentMatch();
/**
Returns true if there are adjacent operators
*/
	bool isOperAdj();
/**
Parses out data and sends it to the in-member vector
*/
	void toVector();
/**
Returns, as a string, the calculated value--given the operator and the two numbers
@param num1: first number in sequence to be operated on
@param num2: second number in sequence to be operated on
@param opSym: the operator symbol
*/
	string calculation(string num1, string num2, string opSym);
/**
Returns true if function is %/*, in that order, and returns false if function is +-, in that order
*/
	int isPrecOne(string value);
/**
Counts and returns a value indicating the number of operators in the expression
*/
	int operationCount(vector<string> &things);
/** 
Return the integer value of the infix expression 
*/
	int value();
/** Return the infix items from the expression
Throw an error if the expression
1) is not balanced.
2) the number of operators IS NOT one less than the number of operands.
3) there are adjacent operators. */
	string infix();
/** 
Return a postfix representation of the infix expression 
*/
	string postfix();
/** 
(BONUS) Return a prefix representation of the infix expression 
*/
	string prefix();
/** 
Return the infix vector'd expression items 
*/
	string toString();
	string toString() const;

	~Expression() {};
};

#endif