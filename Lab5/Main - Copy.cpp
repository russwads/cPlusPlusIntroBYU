/**
LAB 5 -- Shunting Yard Algorithm / Expressions
by Rusty Steel Wool

"In computer science, the shunting-yard algorithm is a method
for parsing mathematical expressions specified in infix notation.
It can produce either a postfix notation string, also known as
Reverse Polish notation, or an abstract syntax tree.
A similar algorithm produces a prefix expression (known as 
Polish notation). The algorithm was invented by Edsger Dijkstra 
and is named the 'shunting yard' algorithm because its operation 
resembles that of a rail road shunting yard."
*/

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK;
#endif

#include<iostream>
#include<string>
#include<fstream>
#include<stack>
#include<vector>
#include<sstream>
#include<algorithm>
#include"ExpressionManager.h"
#include"ExpressionManagerInterface.h"

using namespace std;

int main(int argc, char* argv[])
{
//*****************************************************************************************
// Opening in files and verifying argument count
	if (argc < 3) 
	{ 
		cout << "Insufficient number of arguments. Closing..." << endl;
		return -1; 
	}
	ifstream in(argv[1]);
	if (!in) 
	{ 
		cout << "Opening input file failed. Closing..." << endl;
		return -1;
	}
	ofstream out(argv[2]);
	if (!out) 
	{ 
		cout << "Opening output file failed. Closing..." << endl;
		return -1; 
	}
	cout << "Opening files successful!" << endl;

//*****************************************************************************************
// Reading In Files and Creating Expression Information
	string line;
	while (getline(in, line))
	{
		out << line << endl;
		int ls = line.size();
		string eXp = line.substr(12, ls);
		Expression newExp(eXp);
		string infixRes = newExp.infix();
		out << "Infix: " << infixRes << endl;
		infixRes = infixRes.substr(0, 5);
		if (infixRes != "Caught")
		{
			out << "Postfix: " << newExp.postfix() << endl;
//			out << "Prefix: " << newExp.prefix() << endl;
//			out << "Value: " << newExp.value() << endl;
		}
		out << endl;
	}

//*****************************************************************************************
// Freeing Memory to Prevent Memory Leaks and Closing Files
// Closing Program
	in.close();
	out.close();
	cout << "Closing..." << endl;
	string inside;
	getline(cin, inside);
	return 0;
}