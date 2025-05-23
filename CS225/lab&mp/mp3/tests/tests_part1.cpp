#include "catch.hpp"
#include "tests_helper.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "../cs225/PNG.h"
#include "../cs225/HSLAPixel.h"

#include "../list.h"

using namespace cs225;


TEST_CASE("List::insertFront", "[weight=1][part=1]") {
  List<int> list;
  for (unsigned i = 0; i < 10; i++) { list.insertFront(i); }
  REQUIRE(list.size() == 10);
}

TEST_CASE("List::insertBack", "[weight=1][part=1]") {
  List<int> list;
  for (unsigned i = 0; i < 10; i++) { list.insertBack(i); }
  REQUIRE(list.size() == 10);
}

TEST_CASE("List::reverse", "[weight=1][part=1]") {
  PNG in;        in.readFromFile("tests/alma.png");
  PNG expected;  expected.readFromFile("tests/expected-reverse.png");

  List<HSLAPixel> list = imageToList(in);
  list.reverse();
  PNG out = listToImage(list, in.width(), in.height());
  out.writeToFile("actual-reverse.png");
  INFO("Output image `out` saved as actual-reverse.png");

  REQUIRE( out == expected );
}
TEST_CASE("List::reverseNth #1_", "[weight=1][part=1]") {
  List<int> list;
  list.insertBack(2);
  list.insertBack(3);
  list.insertBack(4);
  list.insertBack(5);
  list.insertBack(6);
  list.insertBack(7);
  list.insertBack(8);
  list.reverseNth(2);
  INFO("Output image `out` saved as actual-reverseN_1.png");
  REQUIRE( true );
}


TEST_CASE("List::reverseNth #1", "[weight=1][part=1]") {
  PNG in;        in.readFromFile("tests/alma.png");
  PNG expected;  expected.readFromFile("tests/expected-reverseN_1.png");

  List<HSLAPixel> list = imageToList(in);
  list.reverseNth(in.height() * 20);

  PNG out = listToImage(list, in.width(), in.height());
  out.writeToFile("actual-reverseN_1.png");
  INFO("Output image `out` saved as actual-reverseN_1.png");

  REQUIRE( out == expected );
}

TEST_CASE("List::reverseNth #2", "[weight=1][part=1]") {
  PNG in;        in.readFromFile("tests/alma.png");
  PNG expected;  expected.readFromFile("tests/expected-reverseN_2.png");

  List<HSLAPixel> list = imageToList(in);
  list.reverseNth(in.height() * 61);

  PNG out = listToImage(list, in.width(), in.height());
  out.writeToFile("actual-reverseN_2.png");
  INFO("Output image `out` saved as actual-reverseN_2.png");

  REQUIRE( out == expected );
}

TEST_CASE("List::waterfull1", "[weight=1][part=1]") {
  List<int> list;
  list.insertBack(2);
  list.insertBack(3);
  list.insertBack(4);
  list.insertBack(5);
  list.insertBack(6);
  list.insertBack(7);
  list.insertBack(8);
  list.waterfall();
  INFO("Output image `out` saved as actual-reverseN_1.png");
  REQUIRE( true );
}

TEST_CASE("List::waterfall", "[weight=1][part=1]") {
  PNG in;        in.readFromFile("tests/alma.png");
  PNG expected;  expected.readFromFile("tests/expected-waterfall.png");

  List<HSLAPixel> list = imageToList(in);
  list.waterfall();
  PNG out = listToImage(list, in.width(), in.height());
  out.writeToFile("actual-waterfall.png");
  INFO("Output image `out` saved as actual-waterfall.png");

  REQUIRE( out == expected );
}
