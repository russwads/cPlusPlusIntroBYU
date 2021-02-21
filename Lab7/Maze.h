#ifndef MAZE_H
#define MAZE_H

#include"MazeInterface.h"
#include<string>
#include<sstream>
#include<vector>

using std::string;
using std::ostringstream;
using std::vector;

class Maze : public MazeInterface
{
private:
	int*** maze_data;
	int maze_h = 0;
	int maze_w = 0;
	int maze_l = 0;
	vector<string> mz;
	string*** maze_print;
public:
	enum CellValue { OPEN, BLOCKED, PATH, EXIT, TEMPORARY };
	Maze();
	Maze(int height, int width, int layer);

/**
RECURSIVE FUNCTION
Takes in 0,0,0 to begin function, and continues through
the function by testing each way the maze can press forward.
@param x layer
@param y width
@param z height
*/
	bool pathFinder(int x, int y, int z);
	/** Set print value
	@parm height
	@parm width
	@parm layer
	@parm value
	*/
	void setPrint();
/** Set maze value
	@parm height
	@parm width
	@parm layer
	@parm value
	*/
	void setValue(int height, int width, int layer, int value);
/** Solve maze
	@return true if solveable, else false
	*/
	bool find_maze_path();
/** Output maze (same order as input maze)
	@return string of 2D layers
	*/
	string toString() const;
	~Maze();
};

#endif