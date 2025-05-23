/**
 * @file huffman_tree.cpp
 * Implementation of a Huffman Tree class.
 *
 * @author Chase Geigle - Created
 * @author Nathan Walters - Modified
 * @date Summer 2012
 * @date Fall 2017
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <regex>
#include <utility>

#include "frequency.h"
#include "tests/catch.hpp"
#include "huffman_tree.h"

using namespace std;

HuffmanTree::HuffmanTree(vector<Frequency> frequencies) {
  std::stable_sort(frequencies.begin(), frequencies.end());
  buildTree(frequencies);
  vector<bool> path;
  buildMap(root_, path);
}

HuffmanTree::HuffmanTree(const HuffmanTree &other) { copy(other); }

HuffmanTree::HuffmanTree(BinaryFileReader &bfile) {
  root_ = readTree(bfile);
  vector<bool> path;
  buildMap(root_, path);
}

HuffmanTree::~HuffmanTree() { clear(root_); }

const HuffmanTree &HuffmanTree::operator=(const HuffmanTree &rhs) {
  if (this != &rhs) {
    clear(root_);
    copy(rhs);
  }
  return *this;
}

void HuffmanTree::clear(TreeNode *current) {
  if (current == NULL)
    return;
  clear(current->left);
  clear(current->right);
  delete current;
}

void HuffmanTree::copy(const HuffmanTree &rhs) { root_ = copy(rhs.root_); }

HuffmanTree::TreeNode *HuffmanTree::copy(const TreeNode *current) {
  if (current == NULL)
    return NULL;
  TreeNode *node = new TreeNode(current->freq);
  node->left = copy(current->left);
  node->right = copy(current->right);
  return node;
}

HuffmanTree::TreeNode *
HuffmanTree::removeSmallest(queue<TreeNode *> &singleQueue,
                            queue<TreeNode *> &mergeQueue) {

  /**
   * @todo Your code here!
   *
   * Remove the smallest TreeNode * from the two queues given as
   * parameters. The entries on the queues are in sorted order, so the
   * smaller of the two queues heads is the smallest item in either of
   * the queues. Return this item after removing it from its queue.
   */
  // your code!
  TreeNode *smallest = NULL;
  if (singleQueue.empty())
    smallest = mergeQueue.front(), mergeQueue.pop();
  else if (mergeQueue.empty())
    smallest = singleQueue.front(), singleQueue.pop();
	else if (mergeQueue.front()->freq.getFrequency() < singleQueue.front()->freq.getFrequency())
		smallest = mergeQueue.front(), mergeQueue.pop();
	else
		smallest = singleQueue.front(), singleQueue.pop();
  return smallest;
}

void HuffmanTree::buildTree(const vector<Frequency> &frequencies) {
  queue<TreeNode *> singleQueue; // Queue containing the leaf nodes
  queue<TreeNode *> mergeQueue;  // Queue containing the inner nodes

  /**
   * @todo Your code here!
   *
   * First, place all of the leaf nodes into the singleQueue in
   * increasing order of frequency. Note: frequencies is already sorted
   * for you.
   *
   * Next, until there is only one node on the two queues (that is, one
   * of the queues is empty and one has a single node), remove the two
   * smallest entries from the two queues. Then, create a new internal
   * node with these nodes as children, whose frequency is the sum of
   * these two children's frequencies. Place the new internal node onto
   * the back of the mergeQueue.
   *
   * Finally, when there is a single node left, it is the root. Assign it
   * to the root and you're done!
   */
  for (auto it = frequencies.begin(); it != frequencies.end(); ++it) {
    TreeNode *new_node =
        new TreeNode(*it);
    singleQueue.push(new_node);
  }
	int cnt = singleQueue.size();
  if (cnt == 1)
  {
    TreeNode* nodeInfo = removeSmallest(singleQueue, mergeQueue);
    TreeNode *new_node = new TreeNode(Frequency(nodeInfo->freq.getCharacter(), nodeInfo->freq.getFrequency()));
    root_ = new_node;
    root_->left = NULL;
    root_->right = NULL;
  }
  else if (cnt == 0)
  {
    root_ = new TreeNode(0);
    root_->left = NULL;
    root_->right = NULL;
  }
  for (int i = 1; i < cnt; ++i) {
    TreeNode *mergeNode[2];
    for (int j = 0; j < 2; ++j)
      mergeNode[j] = removeSmallest(singleQueue, mergeQueue);
    int new_freq =
        mergeNode[0]->freq.getFrequency() + mergeNode[1]->freq.getFrequency();
    TreeNode *new_node = new TreeNode(new_freq);
    new_node->left = mergeNode[0], new_node->right = mergeNode[1];
		mergeQueue.push(new_node);
		root_ = new_node;
  }
}

string HuffmanTree::decodeFile(BinaryFileReader &bfile) {
  stringstream ss;
  decode(ss, bfile);
  return ss.str();
}

void HuffmanTree::decode(stringstream &ss, BinaryFileReader &bfile) {
  TreeNode *current = root_;
  while (bfile.hasBits()) {
    /**
     * @todo Your code here!
     *
     * This code is reading in all of the bits in the binary file
     * given. After reading a bit, we go left if the bit was a 0 (or
     * false), and we go right if the bit was a 1 (or true).
     *
     * Special case: if we are at a leaf node, we should "print" its
     * character to the stringstream (with operator<<, just like cout)
     * and start traversing from the root node again.
     */
    int nextBit = bfile.getNextBit();
    if (!nextBit)
      current = current->left;
    else
      current = current->right;
    if (current->freq.getCharacter() != '\0')
      ss << current->freq.getCharacter(), current = root_;
  }
}

void HuffmanTree::writeTree(BinaryFileWriter &bfile) {
  writeTree(root_, bfile);
}

void HuffmanTree::writeTree(TreeNode *current, BinaryFileWriter &bfile) {
  /**
   * @todo Your code here!
   *
   * This code is writing the current HuffmanTree in a compressed format
   * to the given BinaryFileWriter. The strategy for doing so is as
   * follows:
   *      1. If we are a leaf node, write the bit "1" followed by the
   *         byte that is the character of this node.
   *      2. If we are an internal node, writ the bit "0", and then
   *         encode the left and right subtree, recursively.
   *
   * Note that we don't encode the frequencies in this compressed
   * version: this is fine, as the structure of the tree still reflects
   * what the relative frequencies were.
   */
  if (current->freq.getCharacter() != '\0') {
    bfile.writeBit(1);
    bfile.writeByte(current->freq.getCharacter());
    return;
  }
  bfile.writeBit(0);
  if (current->left)
    writeTree(current->left, bfile);
  if (current->right)
    writeTree(current->right, bfile);
}

HuffmanTree::TreeNode *HuffmanTree::readTree(BinaryFileReader &bfile) {
  /**
   * @todo Your code here!
   *
   * This code is reading a HuffanTree in from a file in the format that
   * we wrote it above. The strategy, then, is as follows:
   *      1. If the file has no more bits, we're done.
   *      2. If we read a 1 bit, we are a leaf node: create a new
   *         TreeNode with the character that is the next byte in the
   *         file (its frequency should be 0, since we are ignoring
   *         frequency data now).
   *      3. If we read a 0 bit, create a new internal node (with
   *         frequency 0, since we are ignoring them now, and set its left
   *         child and right children to be the subtrees built recursively.
   *      4. Your function should return the TreeNode it creates, or NULL
   *         if it did not create one.
   */
  if (!bfile.hasBits())
    return NULL;
  int nextBit = bfile.getNextBit();
  TreeNode *new_node;
  if (nextBit) {
    if (!bfile.hasBytes())
      return NULL;
    char character = bfile.getNextByte();
    new_node = new TreeNode(Frequency(character, 0));
    return new_node;
  }
  new_node = new TreeNode(Frequency('\0', 0));
  new_node->left = readTree(bfile);
  new_node->right = readTree(bfile);
  return new_node;
}

void HuffmanTree::buildMap(TreeNode *current, vector<bool> &path) {
  // Base case: leaf node.
  if (current->left == NULL && current->right == NULL) {
    bitsMap_[current->freq.getCharacter()] = path;
    return;
  }

  // Move left
  path.push_back(false);
  buildMap(current->left, path);
  path.pop_back();

  // Move right
  path.push_back(true);
  buildMap(current->right, path);
  path.pop_back();
}

void HuffmanTree::printInOrder() const {
  printInOrder(root_);
  cout << endl;
}

void HuffmanTree::printInOrder(const TreeNode *current) const {
  if (current == NULL)
    return;
  printInOrder(current->left);
  cout << current->freq.getCharacter() << ":" << current->freq.getFrequency()
       << " ";
  printInOrder(current->right);
}

void HuffmanTree::writeToFile(const string &data, BinaryFileWriter &bfile) {
  for (auto it = data.begin(); it != data.end(); ++it)
    writeToFile(*it, bfile);
}

void HuffmanTree::writeToFile(char c, BinaryFileWriter &bfile) {
  vector<bool> bits = getBitsForChar(c);
  for (auto it = bits.begin(); it != bits.end(); ++it)
    bfile.writeBit(*it);
}

vector<bool> HuffmanTree::getBitsForChar(char c) { return bitsMap_[c]; }

// class for generic printing

template <typename TreeNode>
class HuffmanTreeNodeDescriptor
    : public GenericNodeDescriptor<HuffmanTreeNodeDescriptor<TreeNode>> {
public:
  HuffmanTreeNodeDescriptor(const TreeNode *root)
      : subRoot_(root) { /* nothing */ }

  string key() const {
    std::stringstream ss;
    char ch = subRoot_->freq.getCharacter();
    int freq = subRoot_->freq.getFrequency();

    // print the sum of the two child frequencies
    if (ch == '\0')
      ss << freq;
    // print the leaf containing a character and its count
    else {
      if (ch == '\n')
        ss << "\\n";
      else
        ss << ch;
      ss << ":" << freq;
    }
    return ss.str();
  }

  bool isNull() const { return subRoot_ == NULL; }
  HuffmanTreeNodeDescriptor left() const {
    return HuffmanTreeNodeDescriptor(subRoot_->left);
  }
  HuffmanTreeNodeDescriptor right() const {
    return HuffmanTreeNodeDescriptor(subRoot_->right);
  }

private:
  const TreeNode *subRoot_;
};

int HuffmanTree::height(const TreeNode *subRoot) const {
  if (subRoot == NULL)
    return -1;
  return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

void HuffmanTree::print(std::ostream &out) const {
  int h = height(root_);
  if (h > _max_print_height) {
    out << "Tree is too big to print. Try with a small file (e.g. "
           "data/small.txt)"
        << endl;
    return;
  }

  printTree(HuffmanTreeNodeDescriptor<TreeNode>(root_), out);
}
