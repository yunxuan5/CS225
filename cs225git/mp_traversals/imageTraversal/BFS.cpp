#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance) {  
  /** @todo [Part 1] */
  png_ = png;
  start_ = start;
  tolerance_ = tolerance;
  BFStraversal_.push(start_);
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
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(this, png_, start_, tolerance_, visited);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */
  BFStraversal_.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */
  Point front = BFStraversal_.front();
  if(BFStraversal_.empty()){
    return Point(-1, -1);
  }
  BFStraversal_.pop();
  return front;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  /** @todo [Part 1] */
  Point front = BFStraversal_.front();
  if(BFStraversal_.empty()){
    return Point(-1, -1);
  }
  return front;
}
/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  return BFStraversal_.empty();
}

int BFS::getVisited(Point visitPoint){
  return visited[visitPoint.x][visitPoint.y];
}

void BFS::setVisited(Point visitPoint){
  visited[visitPoint.x][visitPoint.y] = 1;
}
