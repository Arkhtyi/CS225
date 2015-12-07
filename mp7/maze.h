/* Your code here! */

#include "dsets.h"
#include "png.h"

#include <vector>
#include <iostream>
#include <queue>

using std::vector;

class SquareMaze{

// X = i%width
// Y = i/width
// getId = width*y+x


private:

	vector<bool> right;
	vector<bool> down;
	vector<bool> visited;
	DisjointSets section;
	vector<int> path;
	std::queue<int> Q;
	int wid;
	int hi;

public:

	SquareMaze();

	int getx(int i, int width);
	
	int gety(int i, int width);

	int getId(int x, int y, int width) const;

	void makeMaze(int width, int height);

	bool canTravel(int x,int y,int dir) const;
	
	void setWall(int x, int y, int dir, bool exists);
	
	vector <int> solveMaze();
	
	PNG* drawMaze()const;
	
	PNG* drawMazeWithSolution();




};
