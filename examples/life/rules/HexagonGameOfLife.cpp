//
// Created by atolstenko on 2/9/2023.
//

#include "HexagonGameOfLife.h"

#include <iostream>
void HexagonGameOfLife::Step(World& world) {

  for (int i = 0; i < world.SideSize(); i++) { // it would be better to only iterate though the tiles that are alive or neighboring an alive tile. an unordered map is faster than a map
    for (int j = 0; j < world.SideSize(); j++) {


      Point2D point = Point2D(i, j);
      int count = CountNeighbors(world, point);
      bool isAlive = world.Get(point);

    //  if (isAlive) {CountNeighbors(world, point);}

      if (count == 2) {world.SetNext(point, true);}else{world.SetNext(point, false);}


    }
  }

}
int HexagonGameOfLife::CountNeighbors(World& world, Point2D point) {

  int num = 0;

  for (int y = -1 ; y <= 1 ; y++) {

    bool isYOdd = abs(y% 2) == 1;
    bool isROdd = point.y % 2 == 1;

    for (int x = -1 + (isYOdd && isROdd); x <= 1 - (isYOdd && !isROdd); x++) {

      if (true) {
      //  world.SetNext(Point2D(point.x + x, point.y + y), true);
        num += world.Get(Point2D(point.x + x, point.y + y));
      }

    }
  }
  num -= world.Get(point);

  return num;
}
