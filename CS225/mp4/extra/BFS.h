#ifndef BFS_H
#define BFS_H

#include <cmath>
#include <iterator>
#include <list>
#include <queue>

#include "../Point.h"
#include "../cs225/PNG.h"

#include "ImageTraversal.h"

using namespace cs225;

/**
 * A breadth-first ImageTraversal.
 */
class BFS : public ImageTraversal {
public:
  BFS(const PNG &png, const Point &start, double tolerance);

  ImageTraversal::Iterator begin();
  ImageTraversal::Iterator end();

  void add(const Point &point);
  Point pop();
  Point peek() const;
  bool empty() const;

private:
  queue<Point> toGo;
};

#endif
