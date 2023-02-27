#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  current = Point(-1, -1);
}

ImageTraversal::Iterator::Iterator(ImageTraversal* traversal, PNG png, Point start, double tolerance, vector<vector<int>> visited){
  IteratorPNG = png;
  IteratorStart = start;
  IteratorTolerance = tolerance;
  IteratorTraversal = traversal;
  current = IteratorTraversal->peek();
  IteratorVisited = visited;
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */

  Point poppoint = IteratorTraversal->pop();
  HSLAPixel &startPixel = IteratorPNG.getPixel(poppoint.x, poppoint.y);
  HSLAPixel &iterpixel = IteratorPNG.getPixel(IteratorStart.x, IteratorStart.y);

  Point right(poppoint.x + 1, poppoint.y);
  if(right.x < IteratorPNG.width() && right.x >= 0 && right.y < IteratorPNG.height() && right.y >= 0){
    if(IteratorVisited[right.x][right.y] == 0){
      HSLAPixel & otherPixel = IteratorPNG.getPixel(right.x, right.y);
      Point otherPoint(right.x, right.y);
      if(calculateDelta(otherPixel, iterpixel) <= IteratorTolerance){
        IteratorTraversal->add(otherPoint);
      }
    }
  }

  Point down(poppoint.x, poppoint.y + 1);
  if(down.x < IteratorPNG.width() && down.x >= 0 && down.y < IteratorPNG.height() && down.y >= 0){
    if(IteratorVisited[down.x][down.y] == 0){
      HSLAPixel & otherPixel = IteratorPNG.getPixel(down.x, down.y);
      Point otherPoint(down.x, down.y);
      if(calculateDelta(otherPixel, iterpixel) <= IteratorTolerance){
        IteratorTraversal->add(otherPoint);
      }
    }
  }
  
  Point left(poppoint.x - 1, poppoint.y);
  if(left.x < IteratorPNG.width() && left.x >= 0 && left.y < IteratorPNG.height() && left.y >= 0){
    if(IteratorVisited[left.x][left.y] == 0){
      HSLAPixel & otherPixel = IteratorPNG.getPixel(left.x, left.y);
      Point otherPoint(left.x, left.y);
      if(calculateDelta(otherPixel, iterpixel) <= IteratorTolerance){
        IteratorTraversal->add(otherPoint);
      }
    }
  }

  Point up(poppoint.x, poppoint.y - 1);
  if(up.x < IteratorPNG.width() && up.x >= 0 && up.y < IteratorPNG.height() && up.y >= 0){
    if(IteratorVisited[up.x][up.y] == 0){
      HSLAPixel & otherPixel = IteratorPNG.getPixel(up.x, up.y);
      Point otherPoint(up.x, up.y);
      if(calculateDelta(otherPixel, iterpixel) <= IteratorTolerance){
        IteratorTraversal->add(otherPoint);
      }
    }
  }

  IteratorVisited[poppoint.x][poppoint.y] = 1;
  current = IteratorTraversal->peek();

  while(IteratorTraversal->empty() == false && IteratorVisited[IteratorTraversal->peek().x][IteratorTraversal->peek().y] == 1){
    current = IteratorTraversal->pop();
    current = IteratorTraversal->peek();
  }
  if(IteratorTraversal->empty()){
    return *this;
  }
  current = IteratorTraversal->peek();
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return this->current;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  if(this->current == other.current){
    return false;
  }
  else{
    return true;
  }
}

