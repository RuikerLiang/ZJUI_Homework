#ifndef FLOODFILLEDIMAGE_H
#define FLOODFILLEDIMAGE_H

#include "cs225/PNG.h"
#include <list>
#include <iostream>

#include "colorPicker/ColorPicker.h"
#include "imageTraversal/ImageTraversal.h"

#include "Point.h"
#include "Animation.h"

using namespace cs225;

class FloodFilledImage
{
public:
  FloodFilledImage(const PNG &png);
  void addFloodFill(ImageTraversal &traversal, ColorPicker &colorPicker);
  Animation animate(unsigned frameInterval) const;
  vector<ImageTraversal *> _flood;
  vector<ColorPicker *> _colorPicker;

private:
  PNG _image;
};

#endif
