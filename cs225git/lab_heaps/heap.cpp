
#include <cmath>
#include <iostream>
// #include <assert.h>

/**
* @file heap.cpp
* Implementation of a heap class.
*/

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
   // @TODO Update to return the index you are choosing to be your root.

   return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
   // @TODO Update to return the index of the left child.

   return 2 * currentIdx;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
   // @TODO Update to return the index of the right child.

   return 2 * currentIdx + 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
   // @TODO Update to return the index of the parent.

   return std::floor(currentIdx/2);
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
   // @TODO Update to return whether the given node has a child

   return leftChild(currentIdx) < _elems.size();
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
   // @TODO Update to return the index of the child with highest priority
   ///   as defined by higherPriority()


   const T leftElem = _elems[leftChild(currentIdx)];

   // Has no right child
   if(rightChild(currentIdx) >= _elems.size()) { return leftChild(currentIdx); }

   const T rightElem = _elems[rightChild(currentIdx)];

   // Find higher priority child and return it's index
   if(higherPriority(leftElem, rightElem))  { return leftChild(currentIdx); }

   else { return rightChild(currentIdx); }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
   // @TODO Implement the heapifyDown algorithm.

   if(!hasAChild(currentIdx)) {
       return;
   }

   size_t higherPriorityIdx = maxPriorityChild(currentIdx);
   if(higherPriority(_elems[higherPriorityIdx], _elems[currentIdx]))
   {
       std::swap(_elems[currentIdx], _elems[higherPriorityIdx]);
       heapifyDown(higherPriorityIdx);
   }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
   if (currentIdx == root())
   {
       return;
   }

   size_t parentIdx = parent(currentIdx);

   if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
       std::swap(_elems[currentIdx], _elems[parentIdx]);
       heapifyUp(parentIdx);
   }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
   // @TODO Depending on your implementation, this function may or may
   ///   not need modifying

   _elems.push_back(T());
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{
   // @TODO Construct a heap using the buildHeap algorithm

   _elems.push_back(T());

   for(size_t i = 0; i < elems.size(); i++)
   {
       _elems.push_back(elems[i]);
   }

   for(size_t i = _elems.size() - 1; i >= 1; i--)
   {
       heapifyDown(i);
   }

}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
   // @TODO Remove, and return, the element with highest priority

   if(_elems.size() == 2)
   {
       T rootElem = _elems.back();
       _elems.pop_back();
       return rootElem;
   }

   if(!empty())
   {
       T rootElem = _elems[root()];
       std::swap(_elems[root()], _elems.back());
       _elems.pop_back();
       heapifyDown(root());
       return rootElem;
   }

   return T();
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
   // @TODO Return, but do not remove, the element with highest priority

   if(!empty())
   {
       return _elems[root()];
   }

   return T();
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
   // @TODO Add elem to the heap

   _elems.push_back(elem);
   heapifyUp(_elems.size() - 1);
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
   // @TODO In-place updates the value stored in the heap array at idx
   // Corrects the heap to remain as a valid heap even after update

   if(_elems[idx] == elem) return;

   if(higherPriority(elem, _elems[idx]))
   {
       _elems[idx] = elem;

       if(idx == root()) return;

       if(higherPriority(elem, _elems[parent(idx)]))
       {
           heapifyUp(idx);
       }
   }
   else
   {
       _elems[idx] = elem;

       if(!hasAChild(idx)) return;

       if(higherPriority(_elems[maxPriorityChild(idx)], elem))
       {
           heapifyDown(idx);
       }
   }
}


template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
   // @TODO Determine if the heap is empty
   /*
        The heap will be empty if our size is less than our indexing. 
   */
   return _elems.size() <= root();
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
   for (size_t i = root(); i < _elems.size(); i++) {
       heaped.push_back(_elems[i]);
   }
}