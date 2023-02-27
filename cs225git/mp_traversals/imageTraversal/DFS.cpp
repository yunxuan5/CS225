#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"


/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * 
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) {  
  /** @todo [Part 1] */

  png_ = png;
  start_ = start;
  tolerance_ = tolerance;
  DFStraversal_.push(start_);
  unsigned width = png.width();
  unsigned height = png.height();
  visited.resize(width);
  for(unsigned i = 0; i < width; i++){
    visited[i].resize(height);
    for(unsigned j = 0; j < height; j++){
      visited[i][j] = 0;
    }
  }
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(this, png_, start_, tolerance_, visited);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
  DFStraversal_.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
  Point top = DFStraversal_.top();
  if(DFStraversal_.empty()){
    return Point(-1, -1);
  }
  DFStraversal_.pop();
  return top;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
  if(DFStraversal_.empty()){
    return Point(-1, -1);
  }
  return DFStraversal_.top();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  return DFStraversal_.empty();
}

int DFS::getVisited(Point visitPoint){
  return visited[visitPoint.x][visitPoint.y];
}

void DFS::setVisited(Point visitPoint){
  visited[visitPoint.x][visitPoint.y] = 1;
}