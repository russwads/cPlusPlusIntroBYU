/**
LAB 4--LINKED LIST
By Sparta Custard
CS 235

*****I ran out of time, so this is all I was able to accomplish in the small time I had left. 
It struggles to save the Nodes it creates into the actual list, so it only shows up with "True" and Empty Lists.
I hate my life.

"Linked Lists are common data structures in all object-oriented languages,
and will play a vital role in your activities as a programmer.
A Linked List is defined as a list of nodes with access to only the first one,
where a node is defined as an object that contains a value and access to the next node."
*/

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK;
#endif

#include<string>
#include<iostream>
#include<sstream>
#include<fstream>

#include "LinkedList.h"
#include "LinkedListInterface.h"

using namespace std;


/**
Takes the line and delegates the next course of action
@param line: the function that is to be taken place
*/
double Director(string line)
{
	if (line == "insertHead") { return 1.1; } //BOOL
	else if (line == "insertTail") { return 2.2; } //BOOL
	else if (line == "insertAfter") { return 3.3; } //BOOL
	else if (line == "size") { return 4.4; } //INT
	else if (line == "printList") { return 5.5; } //STRING (toString function)
	else if (line == "remove") { return 6.6; } //BOOL
	else if (line == "clear") { return 7.7; } //BOOL
	else if (line == "at") { return 8.8; } //T-VALUE

	else { return -1; }
}
/**
Parses out string data to direct line to correct function
@param in: the file read into the program
@param line: the one line read in that contains a function (and possibly the data)
*/
string initialDirect(string line)
{
	if ((line != "size") && (line != "printList") && (line != "clear"))
	{
		int datafinder = 0;
		while (!isblank(line[datafinder])) { datafinder++; }
		string buffer1 = line.substr(0, datafinder);
		return buffer1;
	}
	else { return line; }
}


int main(int argc, char* argv[])
{
	VS_MEM_CHECK;

	string line;
//Check on Argument list; ensuring that there are 3 arguments
	if (argc < 3)
	{
		cerr << "Insufficient arguments. Exiting..." << endl;
		return -1;
	}

	ifstream in(argv[1]);
	if (!in)
	{
		cerr << "Failure to open in file. Exiting..." << endl;
		return -1;
	}

	ofstream out(argv[2]);
	if (!out)
	{
		cerr << "Failure to open out file. Exiting..." << endl;
		return -1;
	}
	cout << "File Open Successful!" << endl;

//*************************************************************************
// Input and Output Parsing: Reading and Executing Function
	getline(in, line);
	if (line == "INT")
	{
		LinkedList<int> int_list;
		cout << line << " <INT>" << endl;
		while (getline(in, line))
		{
			cout << line << ": ";
			string go_next = initialDirect(line); //Parses out the next function to take place
			double function = Director(go_next); //Sends next function and data to be parsed and instantiated
			if ((function == 1.1)|| (function == 2.2)|| (function == 6.6)|| (function == 8.8))
			{
				int j = 0;
				while (!isblank(line[j])) { j++; } //Parsing through string data to pull out data from input
				j = j + 1; //Accounting for white space
				int llen = line.length();
				string valBuff = line.substr(j, llen); //Creating a "string" version of the Node data
				int value = stoi(valBuff); //Creating an integer value that goes into the LinkedList as Node data (using std function "stoi()")

				bool test;
				if (function == 1.1) { test = int_list.insertHead(value); } //Running insertHead function
				else if (function == 2.2) { test = int_list.insertTail(value); } //Running insertTail function
				else if (function == 6.6) { test = int_list.remove(value); } //Running Remove function
				else if (function == 8.8) { cout << int_list.at(value); } //Running At function
				
				if (function != 8.8) { if (true) { cout << "True"; } if (false) { cout << "False"; } } //Printing Boolean value
			}
			else if (function == 3.3)
			{
				int j = 0;
				while (!isblank(line[j])) { j++; } //Parsing through string data to pull out data from input
				j = j + 1; //Accounting for white space

				int k = j;
				while (!isblank(line[k])) { k++; } //Parsing through first number data to find end of first number

				string mnBuff = line.substr(j, k); //Creating first number in a string data-type
				int matchNode = stoi(mnBuff); //Creating matchNode, an integer value that checks for the node that the new node will be inserted after (using std function "stoi()") 
				k = k + 1;

				int llen = line.length();
				string nBuff = line.substr(k, llen); //Creating a "string" version of the Node data
				int node = stoi(nBuff); //Creating node, an integer value that goes into the LinkedList as Node data (using std function "stoi()")

				bool test = int_list.insertAfter(matchNode, node); //Running insertAfter function
				if (true) { cout << "True"; } if (false) { cout << "False"; } //Printing Boolean value
			}
			else if (function == 4.4) { cout << int_list.size(); } //Creates and prints list size
			else if (function == 5.5) { cout << int_list.toString(); } //Prints list of nodes
			else if (function == 7.7) { bool test = int_list.clear(); if (true) { cout << "True"; } if (false) { cout << "False"; } } //Running Clear function, and prints Boolean value

			cout << endl;
		}
		int_list.clear();
	}
	else if (line == "STRING")
	{
		LinkedList<string> string_list;
		cout << line << " <STRING>" << endl;
		while (getline(in, line))
		{
			cout << line << " ";
			string go_next = initialDirect(line); //Parses out the next function to take place
			double function = Director(go_next); //Sends next function and data to be parsed and instantiated

			if ((function == 1.1) || (function == 2.2) || (function == 6.6))
			{
				int j = 0;
				while (!isblank(line[j])) { j++; } //Parsing through string data to pull out data from input
				j = j + 1; //Accounting for white space
				int llen = line.length();
				string value = line.substr(j, llen); //Creating the value for the Node data

				bool test;
				if (function == 1.1) { test = string_list.insertHead(value); } //Running insertHead function
				else if (function == 2.2) { test = string_list.insertTail(value); } //Running insertTail function
				else if (function == 6.6) { test = string_list.remove(value); } //Running Remove function
				if (test == true) { cout << "True"; } if (test == false) { cout << "False"; } //Printing Boolean value
			}
			else if (function == 3.3)
			{
				int j = 0;
				while (!isblank(line[j])) { j++; } //Parsing through string data to pull out data from input
				j = j + 1; //Accounting for white space

				int k = j;
				while (!isblank(line[k])) { k++; } //Parsing through first number data to find end of first number

				string matchNode = line.substr(j, k); //Creating matchNode, a string value that checks for the node that the new node will be inserted after
				k = k + 1;

				int llen = line.length();
				string node = line.substr(k, llen); //Creating node, a string value that goes into the LinkedList as Node data

				bool test = string_list.insertAfter(matchNode, node); //Running insertAfter function
				if (test == true) { cout << "True"; } if (test == false) { cout << "False"; } //Printing Boolean value
			}
			else if (function == 4.4) { cout << string_list.size(); } //Creates and prints list size
			else if (function == 5.5) { cout << string_list.toString(); } //Prints list of nodes
			else if (function == 7.7) 
			{ 
				bool test = string_list.clear(); 
				if (test == true) { cout << "True"; } 
				if (test == false) { cout << "False"; }
			} //Running Clear function, and prints Boolean value
			else if (function == 8.8)
			{
				int j = 0;
				while (!isblank(line[j])) { j++; } //Parsing through string data to pull out data from input
				j = j + 1; //Accounting for white space
				int llen = line.length();
				string valBuff = line.substr(j, llen); //Creating a "string" version of the Node data
				int value = stoi(valBuff); //Creating an integer value that goes into the LinkedList as Node data (using std function "stoi()")
				cout << string_list.at(value); //Running At function
			}

			cout << endl;
		}
		string_list.clear();
	}


	in.close();
	out.close();
	getline(cin, line);
	return 0;
}