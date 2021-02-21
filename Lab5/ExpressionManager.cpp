#include<stack>
#include<vector>
#include<sstream>
#include<algorithm>
#include<iostream>
#include"ExpressionManager.h"

using namespace std;

int Expression::isOp(string value)
{
	for (int i = 3; i < 8; i++)
	{
		if (value == operators[i]) { return 0; }
	}
	return -1;
}
bool Expression::isoperbal()
{
	int symbcount = 0;
	int numcount = 0;
	for (unsigned int i = 0; i < expression.size(); i++)
	{
		string buffer = expression[i];
		if (isalnum(buffer[0])) { numcount++; }
		if (ispunct(buffer[0])) { symbcount++; }
	}
	symbcount++;
	if (numcount == symbcount) { return true; }
	else { return false; }
}
bool Expression::isParentMatch()
{
	//Start and End data count up parentheses at each end. For function to return true, Start and End must match.
	//Bool members ensure that any one type of parentheses block is not counted twice
	//Parentheses data
	int parentStart = 0;
	int parentEnd = 0;
	bool parent = true;
	//Bracket data
	int brackStart = 0;
	int brackEnd = 0;
	bool brack = true;
	//"Pretty Parentheses" data
	int pparStart = 0;
	int pparEnd = 0;
	bool ppar = true;

	for (unsigned int i = 0; i < inExp.size(); i++)
	{
		string figureOut = inExp.substr(i);
		if ((figureOut == "(") && (parent == true))
		{
			parentStart++;
			for (unsigned int j = 0; j < inExp.size(); j++)
			{
				figureOut = inExp.substr(j);
				if (figureOut == "(") { parentStart++; }
				if (figureOut == ")") { parentEnd++; }
			}
			parent = false;
		}
		if ((figureOut == "{") && (brack == true))
		{
			brackStart++;
			for (unsigned int j = 0; j < inExp.size(); j++)
			{
				figureOut = inExp.substr(j);
				if (figureOut == "(") { brackStart++; }
				if (figureOut == ")") { brackEnd++; }
			}
			brack = false;
		}
		if ((figureOut == "[") && (ppar == true))
		{
			pparStart++;
			for (unsigned int j = 0; j < inExp.size(); j++)
			{
				figureOut = inExp.substr(j);
				if (figureOut == "(") { pparStart++; }
				if (figureOut == ")") { pparEnd++; }
			}
			ppar = false;
		}
	}

	start = parentStart + brackStart + pparStart;
	finish = parentEnd + brackEnd + pparEnd;
	if ((parentStart == parentEnd) && (brackStart == brackEnd) && (pparStart == pparEnd))
	{
		operNum = parentStart + brackStart + pparStart;
		return true;
	}
	else { return false; }
}
bool Expression::isOperAdj()
{
	for (unsigned int i = 0; i < expression.size() - 1; i++)
	{		
		string op1 = expression[i];
		string op2 = expression[i + 1];
		for (unsigned int j = 3; j < operators->size(); j++)
		{
			if (op1 == operators[j]) { op1 = "true"; }
			if (op2 == operators[j]) { op2 = "true"; }
		}
		if ((op1 == "true") && (op2 == "true")) { return true; }
	}
	return false;
}
void Expression::toVector()
{
	istringstream ss (inExp);
	string buffer;
	while (ss)
	{
		ss >> buffer;
		expression.push_back(buffer);
		if (ss.eof()) { break; }
	}
}
string Expression::calculation(string num1, string num2, string opSym)
{
	int number1 = stoi(num1);
	int number2 = stoi(num2);
	if (opSym == "+") { number1 = number1 + number2; }
	if (opSym == "-") { number1 = number1 - number2; }
	if (opSym == "*") { number1 = number1 * number2; }
	if (opSym == "/") { number1 = number1 / number2; }
	if (opSym == "%") { number1 = number1 % number2; }
	ostringstream ss;
	ss << number1;
	return ss.str();
}
int Expression::isPrecOne(string value)
{
	unsigned int i = 3;
	for (; i < 8; i++)
	{
		if (value == operators[i]) { break; }
	}
	return i;
}
int Expression::operationCount(vector<string> &expressio)
{
	int ops = 0;
	for (unsigned int i = 0; i < expressio.size(); i++)
	{
		string hello = expressio[i];
		if (ispunct(hello[0])) { ops = ops + 1; }
	}
	return ops;
}

int Expression::value()
{ /*
	int integer = 0;
	vector<string> operations;
	for (int i = 0; i < postFix.size(); i++)
	{
		while (!postFix.empty())
		{
			operations.push_back(postFix.top());
			postFix.pop();
		}
	}
	for (unsigned int i = 0; i < operations.size(); i++)
	{
		for (unsigned int j = 0; j < operators.size(); j++)
		{
			if (operations[i] == operators.substr(j))
			{
				string newNum = calculation(operations[i - 2], operations[i - 1], operations[i]);
				operations[i - 2] = newNum;

				operations.erase(operations.begin() + (i - 1), operations.begin() + i);
				i = 0;
			}
		}
	}
	string buffer = operations[0];
	integer = stoi(buffer);        
	return integer; */
	return 0;
}
string Expression::infix()
{
//Translates inExp to a vector	
	toVector();
//Parses through the vector and determines if there are any errors; throws accordingly
	try
	{
		bool parent = isParentMatch(); //boolean for parentheses mismatch
		bool adjacent = isOperAdj(); //boolean for adjacent operators
		bool balanced = isoperbal(); //boolean for balanced equation
		if (parent == false) { throw string("("); }
		if (adjacent == true) { throw string(")"); }
		if (balanced == false) { throw string("fail"); }

		ostringstream ss; //Sending each piece of expressionCopy from vector into its infixed form
		for (int i = 0; i < expression.size(); i++)
		{
			ss << expression[i] << " ";
		}
		return ss.str();
	}
	catch (string fail)
	{
		ostringstream ss;
		ss << "Caught Exception: ";
		if (fail == "(") { ss << "Parentheses Mis-match, NOT Infix"; }
		else if (fail == ")") { ss << "Unbalanced, NOT Infix"; }
		else if (fail == "fail") { ss << "NOT Infix"; }
		return ss.str();
	}
	catch (out_of_range& ex)
	{
		ostringstream ss;
		ss << "Caught Exception: NOT Infix";
		return ss.str();
	}
}
string Expression::postfix()
{
	string chain, haha; //strings with which we find operators and create a string representation of our stack data
	vector<string>chain1;
	vector<string>expressionCopy;
	expressionCopy = expression;

//If the expression relies on parentheses to create its calculations
/*	if (operNum > 0) 
	{
		const string closePar[3] = { ")","}","]" };
		string xiftsop;
		unsigned int i = 0;
		for (; i < expressionCopy.size(); i++)
		{
			haha = expressionCopy[i];
			if (isalnum(haha[0]))
			{
				chain += haha += " ";
				chain1.push_back(chain); chain = "";//Adds the first number to the sequence only
				expressionCopy.erase(expressionCopy.begin() + i);
			}
			for (int j = 0; j < 3; j++)
			{
				bool parend = true;
				if (expressionCopy[i] == closePar[j]) //Finds ending parenthetical statement
				{
					for (unsigned int k = i; k >= 0; k--)
					{
						bool neg = true;
						for (int m = 0; m < 3; m++)
						{
							bool go = true;
							if (expressionCopy[k] == operators.substr(m)) //Traverses backwards to find beginning parenthetical statement
							{
								string buffer, newops;
								for (; k < i; k++) //Parses through parentheses data and grabs numbers first, followed by operators
								{
									if (i - k > 4) //Handles cases where multiple operations are found within one set of parentheses
									{
										int z = k;
										string str = expressionCopy[z];
										bool weird = true;
										while (!isalnum(str[0]))
										{
											z++; str = expressionCopy[z];
											if (ispunct(str[0])) // Handling most cases where multiple ops are found (ex. [5+12*3], where 5 was already parsed and added to chain)
											{ 
												string optest1 = expressionCopy[z + 2];
												string optest2 = expressionCopy[z];
												int test1 = isPrecOne(optest1);
												int test2 = isPrecOne(optest2);
												ostringstream ss;
												if ((test2 > test1) || (test2 == test1)) { ss << expressionCopy[z + 1] << " " << expressionCopy[z] << " " << expressionCopy[z + 3] << " " << expressionCopy[z + 2]; }
												else if (test1 > test2) { ss << expressionCopy[z + 1] << " " << expressionCopy[z + 3] << " " << expressionCopy[z + 2] << " " << expressionCopy[z]; }
												chain1.push_back(ss.str());
												expressionCopy.erase(expressionCopy.begin() + z, expressionCopy.begin() + (z + 3));
												weird = false; break; 
											}
										}
										if (weird) //Weird cases that are not present in the test cases given (ex. [5+12*3], where 5 was not parsed and added to chain yet)
										{
											string optest1 = expressionCopy[z + 3];
											string optest2 = expressionCopy[z + 1];
											int test1 = isPrecOne(optest1);
											int test2 = isPrecOne(optest2);
											ostringstream ss;
											if ((test2 > test1) || (test2 == test1)) { ss << expressionCopy[z] << " " << expressionCopy[z + 2] << " " << expressionCopy[z + 1] << " " << expressionCopy[z + 4] << " " << expressionCopy[z + 3] << " "; }
											else if (test1 > test2) { ss << expressionCopy[z] << " " << expressionCopy[z + 2] << " " << expressionCopy[z + 4] << " " << expressionCopy[z + 3] << " " << expressionCopy[z + 1] << " "; }
											chain1.push_back(ss.str());
											expressionCopy.erase(expressionCopy.begin() + z, expressionCopy.begin() + (z + 4));
										}
										k = i; break;
									}
									buffer = expressionCopy[k];
									if (isalnum(buffer[0])) //Adds numbers
									{
										chain += buffer += " ";
										chain1.push_back(chain); chain = "";
										expressionCopy.erase(expressionCopy.begin() + k);
									}
									else //Grabs operator, but does not add to chain until numbers are added first
									{
										for (unsigned int n = 3; n < operators.size(); n++)
										{
											if (buffer == operators.substr(n)) { newops = buffer; expressionCopy.erase(expressionCopy.begin() + k); }
										}
									}
								} //end of parentheses parsing
								chain += newops += " "; //Adding operator now that the numbers have been added
								chain1.push_back(chain); chain = "";
								go = false; neg = false; parend = false;
							}
							if (!go) { break; } //If parentheses match is found, the "for" loop is broken
						}
						if (!neg) { break; } //If parentheses match is found, and data is chained together, the "for" loop is broken
					}
					expressionCopy.erase(expressionCopy.begin() + i); //deletes first parentheses
				}
				if (!parend) { break; } //If parentheses end was found, and all the other loops executed, the "for" loop is broken
			}
			if (i == expressionCopy.size()) { break; } //If the size of the vector has reached the end, the "for" loop is broken
		}
	}
//If the expression does not have any parentheses
	else*/
	{
		haha = expressionCopy[0];
		string haha2;
		if (isalnum(haha[0])) //Grabs and chains together the first number only
		{
			chain += haha += " ";
			chain1.push_back(chain); chain = "";
			ostringstream ss;
			
			if (expressionCopy.size() > 1)
			{
				for (unsigned int i = 1; i < expressionCopy.size(); i++) //Grabs first known operator at beginning of vector
				{
					ostringstream ss;
					haha = expressionCopy[i];
					int truth = isOp(haha);
					if (truth == 0)
					{
						int iter = 1;
						for (unsigned int j = i + 1; j < expressionCopy.size(); j++) //Grabs second known operator at beginning of vector
						{
							haha2 = expressionCopy[j]; //The second operator, starting as the first operator and adding from there
							int hgf = 0;
							hgf = isOp(haha2);
							if (hgf == 0)
							{
								int hehe = isPrecOne(haha);
								int hehe2 = isPrecOne(haha2);
								if (hehe < hehe2)
									//STOP! The next operator has less significance. Therefore, the parsing and operations may begin.
								{
									while (iter != 0)
									{
										if ((j < expressionCopy.size()) && (expressionCopy[j + 1] != "0.00")) { ss << expressionCopy[j + 1] << " "; }
										if (((j - 1) >= 0) && (expressionCopy[j - 1] != "0.00") && (expressionCopy[0] != expressionCopy[j - 1])) { ss << expressionCopy[j - 1] << " "; }
										ss << expressionCopy[j] << " ";
										expressionCopy[j] = "0.00";
										iter--;
										if (j != 0) { j = j - 1; }
									}
								}
								else if (hehe > hehe2)
									//CONTINUE! There is a possibility that the next operator has greater significance.
								{
									haha = haha2; i = j; iter++;
								} //Setup for next iteration
								else if (hehe == hehe2)
									//STOP! (writing some data) and CONTINUE!
									//The operators are the same, so the second operator (haha2) will continue in the loop as (haha), and find another operator to compare to. 
									//The first operator needs to be parsed through as a new operation.
								{
									if ((i < expressionCopy.size()) && (expressionCopy[i + 1] != "0.00")) { ss << expressionCopy[i + 1] << " "; }
									ss << expressionCopy[i] << " ";

									haha = haha2; i = j; iter++; //Setup for next iteration
								}
							}
						} //End of Second operator parsing
						if ((i < expressionCopy.size()) && (expressionCopy[i + 1] != "0.00")) { ss << expressionCopy[i + 1] << " "; }
						if (((i - 1) <= 0) && (expressionCopy[i - 1] != "0.00")) { ss << expressionCopy[i - 1] << " "; }
						ss << expressionCopy[i] << " ";
						string finish = ss.str();
						chain1.push_back(finish);
					}
				}
			}
		}
		else { return "Failure in Code; try again."; }
		ostringstream ss;
		for (int i = 0; i < chain1.size(); i++)
		{
			ss << chain1[i] << " ";
		}
		return ss.str();
	}

	/*
//Entering all data into postFix stack
	int chain1size = chain1.size(); chain1size--;
	for (unsigned int i = chain1size; i >= 0; i--)
	{
		string buffer = chain1[i];
		postFix.push(buffer);
	}
	chain = "";
	for (unsigned int i = 0; i < chain1.size(); i++)
	{
		chain += chain1[i];
	}
	return chain; */ 
}
string Expression::prefix()
{ /*
	ostringstream ss;
	int sizeStack = preFix.size();
	for (int i = 0; i < sizeStack; i++)
	{
		string newWord = preFix.top();
		preFix.pop();
		ss << newWord << " ";
	}
	return ss.str(); */
	return "test";
}
string Expression::toString()
{ /*
	ostringstream ss;
	int sizeStack = inFixs.size();
	for (int i = 0; i < sizeStack; i++)
	{
		string newWord = inFixs.top();
		inFixs.pop();
		ss << newWord << " ";
	}
	return ss.str(); */
	return "test";
}
string Expression::toString() const
{
	ostringstream ss;
	ss << inExp;
	return ss.str();
}
