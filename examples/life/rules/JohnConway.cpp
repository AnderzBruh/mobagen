#include "JohnConway.h"

// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) {
  // todo: implement
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
