#include "Cat.h"
#include "World.h"
#include <stdexcept>

Point2D Cat::Move(World* world) {

  std::vector<Point2D> path = generatePath(world, true);
//  std::cout << path.size() << std::endl;

  if (path.size() == 0) {//
    std::unordered_map<Point2D, bool> visitied;
    std::unordered_set<Point2D> frontier;

    std::vector<Point2D> neighbors = getVisitableNeightbors(world, world->getCat(), visitied, frontier);

    int winningScore = -1;
    Point2D winningPoint;

    for (auto neig: neighbors) {
      int score = getVisitableNeightbors(world, neig, visitied, frontier).size();
      if ( score > winningScore ) {
        winningScore = score;
        winningPoint = neig;
      };
    }


   // auto rand = Random::Range(0, neighbors.size()-1);
   // std::cout << "Cat picking random movement" << std::endl;
    return winningPoint;

  }
  else {
   // std::cout << path.back().x << "," << path.back().y << std::endl;
    std::unordered_map<Point2D, bool> blankVisitied;
    std::unordered_set<Point2D> blankFrontier;
    for (auto point : path) {
      blankFrontier.insert(point);
    }
    std::cout << "Cat path:" << std::endl;
    world->printPathfinding(blankVisitied, blankFrontier);

    return path.back();
  }


}
