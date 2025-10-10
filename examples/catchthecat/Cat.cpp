#include "Cat.h"
#include "World.h"
#include <stdexcept>

Point2D Cat::Move(World* world) {

  std::vector<Point2D> path = generatePath(world);
  std::cout << path.size() << std::endl;

  if (path.size() == 0) {
    std::unordered_map<Point2D, bool> visitied;
    std::unordered_set<Point2D> frontier;

    std::vector<Point2D> neighbors = getVisitableNeightbors(world, world->getCat(), visitied, frontier);

    auto rand = Random::Range(0, neighbors.size());

    return neighbors[rand];

  }
  else {
    std::cout << path.back().x << "," << path.back().y << std::endl;
    return path.back();
  }


}
