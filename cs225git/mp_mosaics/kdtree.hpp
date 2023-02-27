/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if(curDim < 0 || curDim >= Dim){
      return false;
    }
    if(first[curDim] < second[curDim]){
      return true;
    }
    if(first[curDim] > second[curDim]){
      return false;
    }
    else{
      return first < second;
    }
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    double curDistance = 0.0;
    double potDistance = 0.0;

    for(int i = 0; i < Dim; i ++){
      curDistance += (currentBest[i] - target[i]) * (currentBest[i] - target[i]);
      potDistance +=(potential[i] - target[i]) * (potential[i] - target[i]);
    }
    if(potDistance < curDistance){
      return true;
    }
    
    if(potDistance > curDistance){
      return false;
    }

    else{
      return potential < currentBest;
    }
}

template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>>& list, int left, int right, size_t pivotIndex, int dimension){
  Point<Dim> pivotVal = list[pivotIndex];
  swap(list[pivotIndex], list[right]);
  size_t Index = left;
  for(int i = left; i < right; i++){
    if(smallerDimVal(list[i], pivotVal, dimension)){
      swap(list[Index], list[i]);
      Index ++;
    }
  }
  swap(list[right], list[Index]);
  return Index;

}

template <int Dim>
Point<Dim> KDTree<Dim>::select(vector<Point<Dim>>& list, int left, int right, size_t k, int dimension){
  if(left == right){
    return list[left];
  }
  size_t pivotIndex = (left + right)/2;
  pivotIndex = partition(list, left, right, pivotIndex, dimension);

  if(k == pivotIndex){
    return list[k];
  }
  else if(k < pivotIndex){
    return select(list, left, pivotIndex - 1, k, dimension);
  }
  else{
    return select(list, pivotIndex + 1, right, k, dimension);
  }
}

template <int Dim>
void KDTree<Dim>::buildTree(vector<Point<Dim>>& newPoints, int left, int right, int dimension, KDTreeNode*& subroot){
    if(left > right){
      return;
    }
    
    size_t mid = (left + right)/2;
    Point<Dim> midPoint = select(newPoints, left, right, mid, dimension);
    subroot = new KDTreeNode(midPoint);
    size++;
    buildTree(newPoints, left, mid - 1, (dimension + 1) % Dim, subroot->left);
    buildTree(newPoints, mid + 1, right, (dimension + 1) % Dim, subroot->right); 
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    if(newPoints.empty()){
      root = NULL;
      size = 0;
    }
    else{
      vector<Point<Dim>> points = newPoints;
      size = 0;
      buildTree(points, 0, points.size() - 1, 0, root);
    }

}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  _copy(root, other->root);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  _delete(root);
  _copy(root, rhs->root);
  return *this;

}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  _delete(root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    Point<Dim> temp = query;
    Point<Dim> currentBest = root->point;
    NearestNeighbor(root, currentBest, temp, 0);
    return currentBest;
}

template <int Dim>
void KDTree<Dim>::NearestNeighbor(KDTreeNode* curr_node, Point<Dim>& currentBest, Point<Dim>& query, int dimension) const{
  if(curr_node == NULL){
    return;
  }

  KDTreeNode* next_;
  KDTreeNode* other_;
  if(smallerDimVal(curr_node->point, query, dimension)){
    next_ = curr_node->right;
    other_ = curr_node->left;
  }
  else{
    next_ = curr_node->left;
    other_ = curr_node->right;
  }
  NearestNeighbor(next_, currentBest, query, (dimension + 1) % Dim);

  if(shouldReplace(query, currentBest, curr_node->point)){
    currentBest = curr_node->point;
  }

  double radius = 0.0;
  for(int i = 0; i < Dim; i ++){
    radius += (currentBest[i] - query[i]) * (currentBest[i] - query[i]);
  }
  double distance = (curr_node->point[dimension] - query[dimension]) * (curr_node->point[dimension] - query[dimension]);
  if(radius >= distance){
    NearestNeighbor(other_, currentBest, query, (dimension + 1) % Dim);
  }

}

template <int Dim>
void KDTree<Dim>::_copy(KDTreeNode*& curr_node, KDTreeNode*& other){
  if(other == NULL){
    return;
  }
  curr_node = new KDTreeNode(other->point);
  _copy(curr_node->left, other->left);
  _copy(curr_node->right, other->right);
}

template <int Dim>
void KDTree<Dim>::_delete(KDTreeNode*& subroot){
  if(subroot == NULL){
    return;
  }
  _delete(subroot->left);
  _delete(subroot->right);
  delete subroot;
}