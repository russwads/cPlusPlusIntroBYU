/**
LAB 8 -- Binary Search Tree (BST)
by George G. Geef, WDW, Orlando, FL

"A binary search tree (BST), which may sometimes be called an ordered
or sorted binary tree, is a node-based data structure where each node
references a value, a left child, and a right child.

In a Binary Search Tree, the left subtree of a node contains only nodes
with values less than the node's value, the right subtree of a node
contains only nodes with values greater than the node's value, there
are no duplicate nodes, and both left and right subtrees of a node must
also be binary search trees."

*******
*******
TRIED TO WRITE ITERATOR, BUT COULD NOT FIGURE IT OUT IN TIME.
MEMORY LEAKS PRESENT. -5 PTS
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
#include"BST.h"

using namespace std;

int main(int argc, char* argv[])
{
//***************************************************************************************
// Check for Memory Leaks and Opening Files
	VS_MEM_CHECK;
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

//***************************************************************************************
// Parsing In-File Data and Performing Functions/Writing New Data

	BST<int>tree;
	string line, command;
	do
	{
		in >> command;
		if (command == "Add")
		{
			int value = 0; in >> value;
			bool truth = tree.addNode(value);
			out << command << " " << value << " " << boolalpha << truth << endl;
		}
		else if (command == "Remove")
		{
			int value = 0; in >> value;
			bool truth = tree.removeNode(value);
			out << command << " " << value << " " << boolalpha << truth << endl;
		}
		else if (command == "Clear")
		{
			bool truth = tree.clearTree();
			out << command << " " << boolalpha << truth << endl;
		}
		else if (command == "PrintBST")
		{
			string treeout = tree.toString();
			out << command << treeout << endl;
		}
/**		else if (command == "Find")
		{
			int value = 0; in >> value;
			BST<int>::Iterator iter = tree.find(value);
			BST<int>::Iterator end_iter = tree.end();
			if (!(iter != end_iter)) { out << " Not Found"; }
			else { out << " Found " << *iter; }
		}
		else if (command == "Tree")
		{

		}
*/		
		else
		{
			cout << "Syntax Error" << endl;
		}
	} while (getline(in, line));

//***************************************************************************************
// Freeing Memory and Closing Files

	tree.clearTree();
	in.close();
	out.close();
	return 0;
}