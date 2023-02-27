/* Your code here! */
#pragma once
#include <vector>
#include "dsets.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
using namespace std;
using namespace cs225;

class SquareMaze{
    private:
    int _width;
    int _height;
    DisjointSets _disjointsets;
    vector<bool> rightwall;
    vector<bool> downwall;

    public:
    SquareMaze();
    void makeMaze(int width, int height); 
    bool canTravel(int x, int y, int dir) const;
    void setWall(int x, int y, int dir, bool exists);
    vector<int> solveMaze();
    PNG* drawMaze() const;
    PNG* drawMazeWithSolution();
};