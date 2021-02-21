/**
LAB 9 -- Maps and Sets
by Rusty Steel Wool

Welcome to the world of Pokémon! In this world, you can use special 
creatures to battle against each other, and the trainer with the best 
strategy wins. In this lab you will implement a set and a map and 
then use them to create a Pokémon storage and battle system.

************IMPORTANT NOTE!!!***************
I did not finish the Map, so its just the Sets that are working. Curse my job.
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
#include"mySet.h"
#include"myMap.h"

using namespace std;

/** Soritng functions that fill sets and maps */
void pokeSort(ifstream& in, Set<string>& pokemon)
{
	string line;
	while (getline(in, line))
	{
		pokemon.insert(line);
		if (line == "") break;
	}
}
void moveSort(ifstream& in, Set<string>& moves)
{
	string line;
	while (getline(in, line))
	{
		moves.insert(line);
		if (line == "") break;
	}
}

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

	Set<string> pokemon;
	Set<string> moves;
	string line;

	while (getline(in, line))
	{
		if (line == "Pokemon:")
		{
			pokeSort(in, pokemon);
		}
		if (line == "Moves:")
		{
			moveSort(in, moves);
		}
		if (line == "Effectivities:")
		{
			;
		}
		if (line == "Ineffectivities:")
		{
			;
		}
		if (line == "Battles:")
		{
			;
		}
		else { ; }
	}

	out << "Pokemon:" << endl;
	out << pokemon.toString() << endl << endl;
	out << "Moves:" << endl;
	out << moves.toString() << endl;

	in.close();
	out.close();
	return 0;
}

/*Map<string, Set<string>> effectiveTypes;
while (getline(in, line))
{
	while (line >> type)
	{
		effectiveTypes[baseType].insert(type)
	}
}
cout << effectiveTypes; */