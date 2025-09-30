#include "JohnConway.h"

//struct Position {
//  uint32_t x;
//  uint32_t y;
//
//  Position(uint32_t x, uint32_t y) : x(x), y(y) {}
//
//  size_t hash() { return ((uint64_t))
//  }
//
//};



// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) {
  // todo: implement

	for (int i = 0; i < world.SideSize(); i++) { // it would be better to only iterate though the tiles that are alive or neighboring an alive tile. an unordered map is faster than a map
		for (int j = 0; j < world.SideSize(); j++) {


			Point2D point = Point2D(i, j);
            int count = CountNeighbors(world, point);
            bool isAlive = world.Get(point);

			if (isAlive && (count < 2 || count > 3)) {world.SetNext(point, false);}
			if (isAlive && count == 2) {world.SetNext(point, true);}
			if (count == 3) {world.SetNext(point, true);}


		}
	}
}

int JohnConway::CountNeighbors(World& world, Point2D point) {

	int num = 0;

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
            num += world.Get(Point2D(point.x + i, point.y + j));
		}
	}
        num -= world.Get(point);
  // todo: implement
  return num;
}
