/**
 * @file ImageTraversal.h
 */
#pragma once

#include <iterator>
#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"
#include <vector>

using namespace cs225;
using namespace std;

/**
 * A base class for traversal algorithms on images.
 *
 * BFS and DFS will inherit from this class
 * 
 * Each derived class must maintain an ordering of points on an image,
 * through calls to the virtual member functions `add` and `pop`.
 * 
 * A derived class provides a traversal by returning instances of
 * ImageTraversal::Iterator.
 */
class ImageTraversal {
public:
  /**
   * A forward iterator through an ImageTraversal.
   */
  class Iterator : std::iterator<std::forward_iterator_tag, Point> {
  public:
    Iterator(); //Default constructor with nothing passed in
    Iterator(ImageTraversal* traversal, PNG png, Point start, double tolerance, vector<vector<int>> visited);
    //Added in iterator that takes in traversal for iteration, png, start, and tolerance

    Iterator & operator++();
    Point operator*();
    bool operator!=(const Iterator &other);

    /** @todo [Part 1] */
    /** add member functions if necessary*/

  private:
    /** @todo [Part 1] */
    /** add private members here if neccesary*/
    //Private members are identical to original class, are they are needed for 
    //traversal
    Point IteratorStart;
    PNG IteratorPNG;
    double IteratorTolerance;

    ImageTraversal* IteratorTraversal; //Added in pointer Traversal for iterator's operations
    Point current; //Added in current point to keep track of where we are iterating;
    vector<vector<int>> IteratorVisited;


  };

  /**
   * The begining of an iterator
   * Virtual function. Derived class need to implement this
   */
  virtual Iterator begin() = 0;

  /**
   * The end of an iterator
   * Virtual function. Derived class need to implement this
   */
  virtual Iterator end() = 0;

  /**
   * Add new point to the traversal
   * Virtual function. Derived class need to implement this
   */
  virtual void add(const Point & t) = 0;
  /**
   * Remove and return the next point of the traversal
   * Virtual function. Derived class need to implement this
   */
  virtual Point pop() = 0;
  /**
   * Return but not remove the next point of the traversal
   * Virtual function. Derived class need to implement this
   */
  virtual Point peek() const = 0;
  /**
   * To see if the traversal has no points left
   * Virtual function. Derived class need to implement this
   */
  virtual bool empty() const = 0;

  virtual int getVisited(Point visitPoint) = 0;
  virtual void setVisited(Point visitPoint) = 0;

private:
  static double calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2);  
};