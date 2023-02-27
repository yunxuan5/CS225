/* Your code here! */
#include "maze.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <vector>
#include <queue>
#include <stack>
#include <map>

SquareMaze::SquareMaze(){
    _width = 0;
    _height = 0;
}

void SquareMaze::makeMaze(int width, int height){
    _width = width;
    _height = height;
    int mazeSize = width * height;
    _disjointsets.addelements(mazeSize);
    for(int count = 0; count < mazeSize; count++){
        rightwall.push_back(true);
        downwall.push_back(true); 
    }

    int i = 0;
    while(i < mazeSize - 1){
        int x = rand() % width;
        int y = rand() % height;
        int index = x + y * width;
        int xborder = width - 1;
        int yborder = height - 1;
        int wall = rand() % 2;

        if(wall == 1){
            if(rightwall[index] == true && x < xborder && _disjointsets.find(index) != _disjointsets.find(index + 1)){
                rightwall[index] = false;
                _disjointsets.setunion(_disjointsets.find(index), _disjointsets.find(index + 1));
                i++;
            }
        }
        else{
            if(downwall[index] == true && y < yborder && _disjointsets.find(index) != _disjointsets.find(index + width)){
                downwall[index] = false;
                _disjointsets.setunion(_disjointsets.find(index), _disjointsets.find(index + width));
                i++;
            }
        }
    }
}

bool SquareMaze::canTravel(int x, int y, int dir) const{
    if(dir == 0){
        if(x >= _width - 1){
            return false;
        }
        return !rightwall[x + y * _width];
    }
    if(dir == 1){
        if(y >= _height - 1){
            return false;
        }
        return !downwall[x + y * _width];
    }
    if(dir == 2){
        if(x < 1){
            return false;
        }
        return !rightwall[x - 1 + y * _width];
    }
    if(dir == 3){
        if(y < 1){
            return false;
        }
        return !downwall[x + (y - 1) * _width];
    }
    return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists){
    if(dir == 0){
        rightwall[x + y * _width] = exists;
    }
    if(dir == 1){
        downwall[x + y * _width] = exists;
    }
}

vector<int> SquareMaze::solveMaze(){
    vector<int> sol;
    vector<bool> visited;
    vector<int> bottom;
    queue<int> bfs;
    map<int, int> points;
    for(int i = 0; i < _width * _height; i++){
        visited.push_back(false);
    }
    visited[0] = true;

    bfs.push(0);
    while(!bfs.empty()){
        int idx = bfs.front();
        bfs.pop();
        int x = idx % _width;
        int y = idx / _height;

        if(y == _height - 1){
            bottom.push_back(idx);
        }

        if(canTravel(x, y, 0) && visited[idx + 1] == false){
            bfs.push(idx + 1);
            points.insert(pair<int, int>(idx + 1, idx));
            visited[idx + 1] = true;
        }

        if(canTravel(x, y, 1) && visited[idx + _width] == false){
            bfs.push(idx + _width);
            points.insert(pair<int, int>(idx + _width, idx));
            visited[idx + _width] = true;
        }

        if(canTravel(x, y, 2) && visited[idx - 1] == false){
            bfs.push(idx - 1);
            points.insert(pair<int, int>(idx - 1, idx));
            visited[idx - 1] = true;
        }

        if(canTravel(x, y, 3) && visited[idx - _width] == false){
            bfs.push(idx - _width);
            points.insert(pair<int, int>(idx - _width, idx));
            visited[idx - _width] = true;
        }
    }
    
    stack<int> path;
    int node = bottom[bottom.size() - 1];
    while(node != 0){
        int prev = points[node];
        
        if(node == prev + 1){
            path.push(0);
        }
        else if(node == prev + _width){
            path.push(1);
        }
        else if(node == prev - 1){
            path.push(2);
        }
        else if(node == prev - _width){
            path.push(3);
        }
        node = prev;
    }
    int pathsize = path.size();
    for(int i = 0; i < pathsize; i++){
        sol.push_back(path.top());
        path.pop();
    }

    return sol;
}

PNG* SquareMaze::drawMaze() const{
    PNG* _png = new PNG(_width * 10 + 1, _height * 10 + 1);
    for(int y = 0; y < _height; y++){
        for(int x = 0; x < _width; x++){
            if(y == 0){
                for(unsigned k = 0; k < 10; k++){
                    if(x * 10 + k < 1 || x * 10 + k > 9){
                        HSLAPixel &Pixel = _png->getPixel(x * 10 + k, 0);
                        Pixel.l = 0;
                    }
                }
            }
            if(x == 0){
                for(unsigned k = 0; k < 10; k++){
                    HSLAPixel &Pixel = _png->getPixel(0, y * 10 + k);
                    Pixel.l = 0;
                }
            }
            if(!canTravel(x, y, 0)){
                for(unsigned k = 0; k <= 10; k++){
                    HSLAPixel &Pixel = _png->getPixel((x + 1) * 10, y * 10 + k);
                    Pixel.l = 0;
                }
            }
            if(!canTravel(x, y, 1)){
                for(unsigned k = 0; k <= 10; k++){
                    HSLAPixel &Pixel = _png->getPixel(x * 10 + k, (y + 1) * 10);
                    Pixel.l = 0;
                }
            }
        }
    }
    return _png;
}

PNG* SquareMaze::drawMazeWithSolution(){
    PNG* sol_png = drawMaze();
    vector<int> solution = solveMaze();
    int x = 5;
    int y = 5;
    for(size_t i = 0; i < solution.size(); i++){
        if(solution[i] == 0){
            for(int j = 0; j < 10; j++){
                HSLAPixel &Pixel = sol_png->getPixel(x + j, y);
                Pixel.l = 0.5;
                Pixel.h = 0;
                Pixel.s = 1;
            }
            x = x + 10;
        }

        if(solution[i] == 1){
            for(int j = 0; j < 10; j++){
                HSLAPixel &Pixel = sol_png->getPixel(x, y + j);
                Pixel.l = 0.5;
                Pixel.h = 0;
                Pixel.s = 1;
            }
            y = y + 10;
        }

        if(solution[i] == 2){
            for(int j = 0; j < 10; j++){
                HSLAPixel &Pixel = sol_png->getPixel(x - j, y);
                Pixel.l = 0.5;
                Pixel.h = 0;
                Pixel.s = 1;
            }
            x = x - 10;
        }

        if(solution[i] == 3){
            for(int j = 0; j < 10; j++){
                HSLAPixel &Pixel = sol_png->getPixel(x, y - j);
                Pixel.l = 0.5;
                Pixel.h = 0;
                Pixel.s = 1;
            }
            y = y - 10;
        }
    }
    HSLAPixel &Pixel = sol_png->getPixel(x, y);
    Pixel.l = 0.5;
    Pixel.h = 0;
    Pixel.s = 1;
    Pixel.a = 1;
    int wall_x = x - 4;
    int wall_y = y + 5;
    for(int i = 0; i < 9; i++){
        HSLAPixel &wall = sol_png->getPixel(wall_x + i, wall_y);
        wall.l = 1;
        wall.a = 1;
    }
    return sol_png;
}