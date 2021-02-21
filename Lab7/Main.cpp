/**
LAB 7 -- 3D Maze
by Rusty Steel Wool

"Two SCUBA diving buddies have encountered a large,
box-shaped storage facility inside the hull of the
Heian Maru, a 512' submarine tender lying on the
bottom of Truk Lagoon at 108'. The storage facility
is composed of 10' x 10' x 10' cells, some of which
can be entered and some which cannot. The only exterior
walls that are missing are on the front of the storage
facility in the upper left corner, and on the rear of
the storage facility in the lower right corner. The divers
wish to determine a path through the storage facility.
In this lab, you will use recursion to find a path through
the maze or to prove that there is no path."

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
#include<sstream>
#include<vector>

#include"Maze.h"
#include"MazeInterface.h"

using namespace std;

int main(int argc, char* argv[])
{
	VS_MEM_CHECK;
//******************************************************************************************************
//Reading In File and Out File
	if (argc < 3)
	{
		cout << "Insufficient number of arguments. Closing..." << endl;
		return -1;
	}
	ifstream in(argv[1]);
	if (!in)
	{
		cout << "Opening input file failed. Closing..." << endl;
		in.close();
		return -1;
	}
	ofstream out(argv[2]);
	if (!out)
	{
		cout << "Opening output file failed. Closing..." << endl;
		in.close();
		out.close();
		return -1;
	}
	cout << "Opening files successful!" << endl;

//******************************************************************************************************
// Parsing In Data and Figuring Out Maze Solution
	int h = 0; int w = 0; int l = 0; // Height, Width, Layer
	string line;
	in >> h >> w >> l;
	Maze maze_main(h, w, l);
	getline(in, line); getline(in, line);
	for (int i = 0; i < l; ++i) //Layer
	{
		for (int j = 0; j < h; ++j) //Height
		{
			for (int k = 0; k < w; ++k) //Width
			{
				int v = 0;
				in >> v;
				maze_main.setValue(j, k, i, v); //Height, Width, Layer, Value
			}
		}
	}
	maze_main.setPrint();
	out << "Solve Maze:" << endl;
	out << maze_main.toString() << endl << endl;
	bool decision = maze_main.find_maze_path();
	if (decision == true) 
	{
		out << "Solution:" << endl;
		out << maze_main.toString();
	}
	else { out << "No Solution Exists!" << endl; }

//******************************************************************************************************
// Closing Files and Freeing Data to Prevent Memory Leaks

	in.close();
	out.close();
	return 0;
}