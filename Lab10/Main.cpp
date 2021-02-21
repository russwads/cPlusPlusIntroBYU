/**
LAB 10 -- QuickSort
by Rusty Steel Wool

"Quicksort is a sorting algorithm developed by
Tony Hoare that, on average, makes O(n log n)
comparisons to sort n items. It is also known
as partition-exchange sort. In the worst case,
it makes O(n^2) comparisons, though this behavior
is rare. Quicksort is typically faster in practice
than other O(n log n) algorithms. Additionally,
quicksort's sequential and localized memory references
work well with a cache. Quicksort can be implemented
as an in-place partitioning algorithm."

********************IMPORTANT!!!**************************
--Ran out of time while programming Sort() function; SortAll and Sort do not work properly as a result.
--I programmed as much of the Bonus as I could, but it is not quite functional either because SortAll and Sort were not finished.
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
#include"QS.h"

using namespace std;

int main(int argc, char* argv[])
{
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

	QS<int> quicksort;
	string line, command;
	while (getline(in,line))
	{
		int a = 0;
		while ((!isspace(line[a])) && (a != line.length())) { a++; }
		command = line.substr(0, a);
		if (command == "QuickSort")
		{
			int value = 0;
			int b = 10;
			while (isdigit(line[b])) { b++; }
			string valbuff = line.substr(10, b);
			value = stoi(valbuff);
			bool truth = quicksort.createArray(value);
			string okay;
			if (truth == true) { okay = "OK"; }
			else { okay = "Error"; }
			out << command << " " << value << " " << okay << endl;
		}
		else if (command == "AddToArray")
		{
			int value = 0; 
			bool truth; 
			ostringstream ss; 
			int i = 0; 
			unsigned int j = 11;

			while (j < line.length())
			{
				int l = j;
				while ((!isspace(line[j]))&&(j != line.length())) { j++; }
				if (j > line.length()) { j = line.length(); }
				int k = j - 1;
				while (isdigit(line[k])) { k--; }
				string digit = line.substr(l, j - k);
				value = stoi(digit);
				j++;
				if (i != 0) { ss << ","; }
				ss << value;
				i++;
				truth = quicksort.addElement(value);
			}

			string finval = ss.str();
			string okay;
			if (truth == true) { okay = "OK"; }
			else { okay = "Error"; }
			out << command << " " << finval << " " << okay << endl;
		}
		else if (command == "Sort")
		{
			int value1 = 0;
			int value2 = 0;
			int b = 5;
			while (isdigit(line[b])) { b++; }
			string valbuff = line.substr(5, b - 5);
			value1 = stoi(valbuff); b++;

			int c = b;
			while (isdigit(line[b])) { b++; }
			valbuff = line.substr(c, b - c);
			value2 = stoi(valbuff);

			bool truth = quicksort.sort(value1, value2);
			string okay;
			if (truth == true) { okay = "OK"; }
			else { okay = "Error"; }
			out << command << " " << value1 << " " << value2 << " " << okay << endl;
		}
		else if (command == "SortAll")
		{
			bool truth = quicksort.sortAll();
			string okay;
			if (truth == true) { okay = "OK"; }
			else { okay = "Error"; }
			out << command << " " << okay << endl;
		}
		else if (command == "Partition")
		{
			int value1 = 0;
			int value2 = 0;
			int value3 = 0;
			int b = 10;
			while ((isdigit(line[b]))||(ispunct(line[b]))) { b++; }
			string valbuff = line.substr(10, b - 10);
			value1 = stoi(valbuff); b++;

			int c = b;
			while ((isdigit(line[b])) || (ispunct(line[b]))) { b++; }
			valbuff = line.substr(c, b - c);
			value2 = stoi(valbuff); b++;

			c = b;
			while ((isdigit(line[b])) || (ispunct(line[b]))) { b++; }
			valbuff = line.substr(c, b - c);
			value3 = stoi(valbuff);

			int truth = quicksort.partition(value1, value2, value3);
			out << command << " " << value1 << "," << value2 << "," << value3 << " = " << truth << endl;
		}
		else if (command == "MedianOfThree")
		{
			int value1 = 0;
			int value2 = 0;
			int b = 14;
			while (isdigit(line[b])) { b++; }
			string valbuff = line.substr(14, b - 14);
			value1 = stoi(valbuff); b++;

			int c = b;
			while (isdigit(line[b])) { b++; }
			valbuff = line.substr(c, b - c);
			value2 = stoi(valbuff);

			int truth = quicksort.medianOfThree(value1, value2);
			out << command << " " << value1 << "," << value2 << " = " << truth << endl;
		}
		else if (command == "Clear")
		{
			bool truth = quicksort.clear();
			string okay;
			if (truth == true) { okay = "OK"; }
			else { okay = "Error"; }
			out << command << " " << okay << endl;
		}
		else if (command == "PrintArray")
		{
			out << command << " " << quicksort << endl;
		}
		else if (command == "Capacity")
		{
			out << command << " " << quicksort.capacity() << endl;
		}
		else if (command == "Size")
		{
			out << command << " " << quicksort.size() << endl;
		}
		else
		{
			cout << "Syntax Error" << endl;
		}
	}

	in.close();
	out.close();
	return 0;
}