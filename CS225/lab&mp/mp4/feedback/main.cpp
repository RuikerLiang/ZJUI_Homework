
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main()
{

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.

  PNG png;
  png.readFromFile("tests/i.png");
  DFS dfs(png, Point(40, 40), 0.05);
  BFS bfs(png, Point(0, 0), 0.05);
  FloodFilledImage flood(png);
  MyColorPicker colorPicker;
  flood.addFloodFill(dfs, colorPicker);
  flood.addFloodFill(bfs, colorPicker);
  Animation anime = flood.animate(1000);
  PNG finalPng = anime.getFrame(anime.frameCount() - 1);
  finalPng.writeToFile("myFloodFill.png");

  PNG lastFrame = anime.getFrame( anime.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  anime.write("myFloodFill.gif");
  return 0;
}
