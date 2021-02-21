#include "Maze.h"
#include<iostream>

using namespace std;

Maze::Maze()
{
	maze_h++; maze_l++; maze_w++;
	maze_data[0][0][0] = 9001;
}

Maze::Maze(int height, int width, int layer)
{
	this->maze_h = height;
	this->maze_w = width;
	this->maze_l = layer;
// Allocate memory for integer data
	maze_data = new int**[layer]; //Layer
	for (int i = 0; i < layer; ++i) 
	{
		maze_data[i] = new int*[height]; //Height
		for (int j = 0; j < height; ++j)
		{
			maze_data[i][j] = new int[width]; //Width
		}
	}
// Allocate memory for string data
	maze_print = new string**[layer]; //Layer
	for (int i = 0; i < layer; ++i)
	{
		maze_print[i] = new string*[height]; //Height
		for (int j = 0; j < height; ++j)
		{
			maze_print[i][j] = new string[width]; //Width
		}
	}
}

bool Maze::pathFinder(int x, int y, int z) //Layer, Height, Width
{
	ostringstream ss;
	ss << "(" << x << "," << y << "," << z << ")";
	string coordinate = ss.str();
	mz.push_back(coordinate);

	//Base Cases
	if ((x == -1) || (y == -1) || (z == -1) ||
		(x == maze_l) || (y == maze_h) || (z == maze_w) || // If any integer is outside of the maze
		(maze_data[x][y][z] == BLOCKED) || // If data is on an invalid path
		(maze_data[x][y][z] == PATH)) // If we have been on the path before
	{
		mz.pop_back();
		return false;
	}
	if ((x == maze_l - 1) && (y == maze_h - 1) && (z == maze_w - 1)) //If we have reached the end of the maze
	{
		maze_data[x][y][z] = EXIT;
		maze_print[x][y][z] = "3";
		return true;
	}
	maze_data[x][y][z] = PATH;
	maze_print[x][y][z] = "2";
	if (	(pathFinder(x, y, z + 1) == false) && (pathFinder(x, y, z - 1) == false) &&
		(pathFinder(x, y + 1, z) == false) && (pathFinder(x, y - 1, z) == false) &&
		(pathFinder(x + 1, y, z) == false) && (pathFinder(x - 1, y, z) == false)) //RECURSION for Left, Right, Up, Down, In, Out
	{ //Recursive completion of maze proceeds here: if all are consistently false, the first function call returns false, reporting unsolvable maze
		maze_data[x][y][z] = TEMPORARY;
		maze_print[x][y][z] = "4";
		mz.pop_back();
		return false;
	}
	else { return true; } //CORRECT PATH: First function call returns true, indicating maze is solvable
}

void Maze::setPrint()
{
	for (int i = 0; i < maze_l; ++i) //Layer
	{
		for (int j = 0; j < maze_h; ++j) //Height
		{
			for (int k = 0; k < maze_w; ++k) //Width
			{
				int buff = maze_data[i][j][k]; //Grab value
				if (buff == 1) { maze_print[i][j][k] = "X"; } //If value is invalid path, print "X"
				else if (buff == 0) { maze_print[i][j][k] = "_"; } //Else, print "_"
				else { cout << "WT...?"; } //Manifestation of Syntax Error
			}
		}
	}
}

void Maze::setValue(int height, int width, int layer, int value)
{
	maze_data[layer][height][width] = value;
}

bool Maze::find_maze_path()
{
	bool truth = pathFinder(0, 0, 0);//First function call; starting at 0,0,0
	if (truth == true) { return true; }//Solvable maze
	else { return false; }//Unsolvable maze
}

string Maze::toString() const
{
	ostringstream ss;
	for (int i = 0; i < maze_l; ++i)//Layer
	{
		int iter = i + 1;
		ss << "Layer " << iter << ":" << endl;
		for (int j = 0; j < maze_h; ++j)//Height
		{
			for (int k = 0; k < maze_w; ++k)//Width
			{
				ss << maze_print[i][j][k] << " ";
			}
			ss << endl;
		}
	}
	return ss.str();
}

Maze::~Maze()
{
// De-Allocate integer memory to prevent memory leak
	for (int i = 0; i < maze_l; ++i) //Layer
	{
		for (int j = 0; j < maze_h; ++j) //Height
		{
			delete[] maze_data[i][j];
		}
		delete[] maze_data[i];
	}
	delete[] maze_data;//Layer
// De-Allocate string memory to prevent memory leak
	for (int i = 0; i < maze_l; ++i)
	{
		for (int j = 0; j < maze_h; ++j)
		{
			delete[] maze_print[i][j];
		}
		delete[] maze_print[i];
	}
	delete[] maze_print;
}