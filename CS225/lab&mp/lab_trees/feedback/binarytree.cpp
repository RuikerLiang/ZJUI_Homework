#pragma once
#include "binarytree.h"
#include <vector>

/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T> int BinaryTree<T>::height() const {
  // Call recursive helper function on root
  return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T> int BinaryTree<T>::height(const Node *subRoot) const {
  // Base case
  if (subRoot == NULL)
    return -1;

  // Recursive definition
  return 1 + max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T> void BinaryTree<T>::printLeftToRight() const {
  // Call recursive helper function on the root
  printLeftToRight(root);

  // Finish the line
  cout << endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node *subRoot) const {
  // Base case - null node
  if (subRoot == NULL)
    return;

  // Print left subtree
  printLeftToRight(subRoot->left);

  // Print this node
  cout << subRoot->elem << ' ';

  // Print right subtree
  printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T> void BinaryTree<T>::mirror() {
  // your code here
  mirror(root);
}

/**
 * @param a To be swapped
 * @param b To be swapped
 */
template <typename T>
template <typename U>
void BinaryTree<T>::_swap(U &a, U &b) {
  U tmp = b;
  b = a;
  a = tmp;
}

/**
 *
 */
template <typename T> void BinaryTree<T>::mirror(Node *&subRoot) {
  if (subRoot->left)
    mirror(subRoot->left);
  if (subRoot->right)
    mirror(subRoot->right);
  _swap(subRoot->left, subRoot->right);
  return;
}

/**
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T> bool BinaryTree<T>::isOrdered() const {
  // your code here
  return isOrdered(root, T(), T(), false, false);
}

/**
 * @param subRoot
 * @param max
 * @param min
 * @param enable_max
 * @param enable_min
 */
template <typename T>
bool BinaryTree<T>::isOrdered(const Node *subRoot, T max, T min,
                              bool enable_max, bool enable_min) const {
  if ((enable_max && max < subRoot->elem) ||
      (enable_min && subRoot->elem < min))
    return false;
  bool ret = true;
  if (subRoot->left)
    ret &= isOrdered(subRoot->left, subRoot->elem, min, true, enable_min);
  if (subRoot->right)
    ret &= isOrdered(subRoot->right, max, subRoot->elem, enable_max, true);
  return ret;
}

/**
 * creates vectors of all the possible paths from the root of the tree to any
 * leaf node and adds it to another vector. Path is, all sequences starting at
 * the root node and continuing downwards, ending at a leaf node. Paths ending
 * in a left node should be added before paths ending in a node further to the
 * right.
 * @param paths vector of vectors that contains path of nodes
 */
template <typename T>
void BinaryTree<T>::printPaths(vector<vector<T>> &paths) const {
  // your code here
  vector<T> path;
  printPaths(root, path, paths);
}

/**
 * @param subRoot
 * @param curr_path
 * @param paths vector of vectors that contains path of nodes
 */
template <typename T>
void BinaryTree<T>::printPaths(Node *subRoot, vector<T> curr_path,
                               vector<vector<T>> &paths) const {
  curr_path.push_back(subRoot->elem);
  if (subRoot->left == subRoot->right && subRoot->right == NULL) {
    paths.push_back(curr_path);
    return;
  }
  if (subRoot->left)
    printPaths(subRoot->left, curr_path, paths);
  if (subRoot->right)
    printPaths(subRoot->right, curr_path, paths);
  return;
}

/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T> int BinaryTree<T>::sumDistances() const {
	return sumDistances(root, 0);
}

/**
 * @param subRoot
 * @param dep
 */
template <typename T>
int BinaryTree<T>::sumDistances(Node *subRoot, int dep) const {
	int ret = dep;
	if (subRoot->left)
		ret = ret + sumDistances(subRoot->left, dep + 1);
	if (subRoot->right)
		ret = ret + sumDistances(subRoot->right, dep + 1);
	return ret;
}