#ifndef DFS_H
#define DFS_H

#include <cmath>
#include <iterator>
#include <list>
#include <stack>

#include "../Point.h"
#include "../cs225/PNG.h"

#include "ImageTraversal.h"

using namespace cs225;

/**
 * A depth-first ImageTraversal.
 */
class DFS : public ImageTraversal {
public:
  DFS(const PNG &png, const Point &start, double tolerance);

  ImageTraversal::Iterator begin();
  ImageTraversal::Iterator end();

  void add(const Point &point);
  Point pop();
  Point peek() const;
  bool empty() const;

private:
  stack<Point> toGo;
};

#endif
