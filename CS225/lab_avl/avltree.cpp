/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#pragma once
#include "avltree.h"

template <class K, class V> V AVLTree<K, V>::find(const K &key) const {
  return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node *subtree, const K &key) const {
  if (subtree == NULL)
    return V();
  else if (key == subtree->key)
    return subtree->value;
  else {
    if (key < subtree->key)
      return find(subtree->left, key);
    else
      return find(subtree->right, key);
  }
}

template <class K, class V> void AVLTree<K, V>::rotateLeft(Node *&t) {
  functionCalls.push_back("rotateLeft");
  // Stores the rotation name (don't
  // remove this) your code here
  Node *rc = t->right;
  t->right = rc->left;
  rc->left = t;
  t = rc;
}

template <class K, class V> void AVLTree<K, V>::rotateLeftRight(Node *&t) {
  functionCalls.push_back(
      "rotateLeftRight"); // Stores the rotation name (don't remove this)
  // Implemented for you:
  rotateLeft(t->left);
  rotateRight(t);
}

template <class K, class V> void AVLTree<K, V>::rotateRight(Node *&t) {
  functionCalls.push_back("rotateRight"); // Stores the rotation name (don't
                                          // remove this) your code here
  Node *lc = t->left;
  t->left = lc->right;
  lc->right = t;
  t = lc;
}

template <class K, class V> void AVLTree<K, V>::rotateRightLeft(Node *&t) {
  functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't
                                              // remove this) your code here
  rotateRight(t->right);
  rotateLeft(t);
}

template <class K, class V> void AVLTree<K, V>::rebalance(Node *&subtree) {
  // your code here
  auto updateHeight = [](Node *&poi) {
    poi->height = 1;
    if (poi->left)
      poi->height = max(poi->left->height + 1, poi->height);
    if (poi->right)
      poi->height = max(poi->right->height + 1, poi->height);
  };
  auto updateAll = [updateHeight](Node *&poi) {
    if (poi->left)
      updateHeight(poi->left);
    if (poi->right)
      updateHeight(poi->right);
    updateHeight(poi);
  };
  auto bF = [](Node *poi) {
    int res = 0;
    if (poi->left)
      res = res + poi->left->height;
    if (poi->right)
      res = res - poi->right->height;
    return res;
  };
  if (subtree == NULL)
    return;
  updateAll(subtree);
  if (bF(subtree) > 1) {
    if (subtree->left && bF(subtree->left) < 0) {
      rotateLeftRight(subtree);
      updateAll(subtree->left);
    } else
      rotateRight(subtree);
  } else if (bF(subtree) < -1) {
    if (subtree->right && bF(subtree->right) > 0) {
      rotateRightLeft(subtree);
      updateAll(subtree->right);
    } else
      rotateLeft(subtree);
  }
  updateAll(subtree);
}

template <class K, class V>
void AVLTree<K, V>::insert(const K &key, const V &value) {
  insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node *&subtree, const K &key, const V &value) {
  // your code here
  if (subtree == NULL) {
    subtree = new Node(key, value);
    subtree->height = 1;
    return;
  }
  if (key < subtree->key)
    insert(subtree->left, key, value);
  if (key > subtree->key)
    insert(subtree->right, key, value);
  rebalance(subtree);
}

template <class K, class V> void AVLTree<K, V>::remove(const K &key) {
  remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node *&subtree, const K &key) {
  if (subtree == NULL)
    return;

  if (key < subtree->key) {
    // your code here
    remove(subtree->left, key);
  }
  else if (key > subtree->key) {
    // your code here
    remove(subtree->right, key);
  }
  else
  {
    if (subtree->left == NULL && subtree->right == NULL)
    {
      /* no-child remove */
      // your code here
      delete subtree;
      subtree = NULL;
    }
    else if (subtree->left != NULL && subtree->right != NULL)
    {
      /* two-child remove */
      // your code here
      Node* IOP = subtree->left, *prev = subtree;
      while (IOP->right)
        prev = IOP, IOP = IOP->right;
      if (prev == subtree)
        prev->left = NULL;
      else
        prev->right = NULL;
      swap(subtree, IOP);
      delete  IOP;
      /*
      IOP->left = subtree->left;
      IOP->right = subtree->right;
      delete  subtree;
      subtree = IOP;
      */
    }
    else {
      /* one-child remove */
      // your code here
      Node* child = subtree->left == NULL ? subtree->right : subtree->left;
      delete subtree;
      subtree = child;
    }
    // your code here
  }
  rebalance(subtree);
}
