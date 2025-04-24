#include <iterator>
#include <cmath>
#include <list>
#include <queue>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 */
BFS::BFS(const PNG &png, const Point &start, double tolerance)
{
  /** @todo [Part 1] */
  _png = png;
  _start = start;
  _tolerance = tolerance;
  add(start);
  HSLAPixel *stdPix = png.getPixel(start.x, start.y);
  int h = png.height(), w = png.width();
  vector<vector<bool>> vis;
  vis.resize(h);
  for (int i = 0; i < h; ++i)
    vis[i].resize(w, false);
  while (!empty())
  {
    Point curPoi = pop();
    if (vis[curPoi.y][curPoi.x])
      continue;
    vis[curPoi.y][curPoi.x] = true;
    trace.push_back(curPoi);
    for (int i = 0; i < 4; ++i)
    {
      int dx[][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
      int newx = dx[i][0] + curPoi.x, newy = dx[i][1] + curPoi.y;
      if (newx >= w || newy >= h || newx < 0 || newy < 0)
        continue;
      if (vis[newy][newx])
        continue;
      HSLAPixel *newPix = png.getPixel(newx, newy);
      if (calculateDelta(*stdPix, *newPix) > tolerance)
        continue;
      add(Point(newx, newy));
    }
  }
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin()
{
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(this);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end()
{
  /** @todo [Part 1] */
  ImageTraversal::Iterator ret(this);
  ret._current = trace.end();
  return ret;
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point &point)
{
  /** @todo [Part 1] */
  toGo.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop()
{
  /** @todo [Part 1] */
  Point ret = toGo.front();
  toGo.pop();
  return ret;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const
{
  /** @todo [Part 1] */
  return toGo.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const
{
  /** @todo [Part 1] */
  return toGo.empty();
}
