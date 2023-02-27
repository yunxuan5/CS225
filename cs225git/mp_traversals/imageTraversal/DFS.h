/**
 * @file DFS.h
 */

#pragma once

#include <iterator>
#include <cmath>
#include <list>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

using namespace cs225;
using namespace std;

/**
 * A depth-first ImageTraversal.
 * Derived from base class ImageTraversal
 */
class DFS : public ImageTraversal {
public:
  DFS(const PNG & png, const Point & start, double tolerance);

  ImageTraversal::Iterator begin();
  ImageTraversal::Iterator end();

  void add(const Point & point);
  Point pop();
  Point peek() const;
  bool empty() const;
  int getVisited(Point visitPoint);
  void setVisited(Point visitPoint);

private:
	/** @todo [Part 1] */
	/** add private members here*/
  PNG png_;
  Point start_;
  double tolerance_;
  stack<Point> DFStraversal_;
  vector<vector<int>> visited;
};
