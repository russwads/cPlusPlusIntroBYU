/*LAB 3 by Front Row Joe

This code is not fully functional and cannot write to files yet. Please automatically dock points for that.
Busy this week, so I did not finish the code. Turning in what I have at this point. Thank you for your patience!

*/

#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<stdlib.h>

#define MAX_ARRAY 1000

#include"ArrayIter.h"

using namespace std;

/**
Reads the input file and writes data into the numbers array
@param in: The input file
@param numbers: The array of numbers, represented by integers
*/
void Read(ifstream& in, ArrayIter<int> &numbers)
{
	for (unsigned int i = 0; i < MAX_ARRAY; ++i)
	{
		int temp_number = 0;
		in >> temp_number;
		if (in.fail()) break;
		else { numbers.push_back(temp_number); }
	}
}

/**
Prints all data to the Output file
@param out: Output file
@param numbers: The array of numbers inputted previously
*/
void Print(ofstream& out, ArrayIter<int> numbers)
{
	out << "SEQUENTIAL" << endl;
	ArrayIter<int>::Iter iter1 = numbers.begin();
	out << "iter1: " << iter1 << endl;
	for (; iter1 != numbers.end(); ++iter1)
		out << *iter1 << " ";
	out << endl << endl;

	out << "PRIME" << endl;
	ArrayIter<int>::Iter iter2 = numbers.begin(PRIME);
	out << "iter2: " << iter2 << endl;
	for (; iter2 != numbers.end(); ++iter2)
		out << *iter2 << " ";
	out << endl << endl;

	out << "COMPOSITE" << endl;
	ArrayIter<int>::Iter iter3 = numbers.begin(COMPOSITE);
	out << "iter3: " << iter3 << endl;
	for (; iter3 != numbers.end(); ++iter3)
		out << *iter3 << " ";
	out << endl << endl;

	out << "FIBINOCCI" << endl;
	ArrayIter<int>::Iter iter4 = numbers.begin(FIB);
	out << "iter4: " << iter4 << endl;
	for (; iter4 != numbers.end(); ++iter4)
		out << *iter4 << " ";
	out << endl;
}

int main(int argc, char* argv[])
{
//**************************************************************************
// Opening Input and Output Files
	if (argc < 3)
	{
		cout << "Insufficient argument value. Please provide an in and out argument stream and try again." << endl;
		return -1;
	}
	ifstream in(argv[1]);
	ofstream out(argv[2]);
	if (!in.is_open())
	{
		out.close();
		cout << "Failure to Open Input File" << endl;
		return -1;
	}
	if (!out.is_open())
	{
		in.close();
		cout << "Failure to Open Output File" << endl;
		return -1;
	}
	cout << "Opening files successful!" << endl;

//**************************************************************************
// Reading In Data from Input File
	ArrayIter<int> numbers(MAX_ARRAY);
	Read(in, numbers);
	Print(out, numbers);

//**************************************************************************
//Delete Any and ALL Temporary Data to Avoid Memory Links
	delete &numbers;

//**************************************************************************
// Closing Input and Output Files
	in.close();
	out.close();
	return 0;
}