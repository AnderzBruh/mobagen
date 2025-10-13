#include "Catcher.h"
#include "World.h"

Point2D Catcher::Move(World* world) {
  // auto side = world->getWorldSideSize() / 2;
  // for (;;) {
  //   Point2D p = {Random::Range(-side, side), Random::Range(-side, side)};
  //   auto cat = world->getCat();
  //   if (cat.x != p.x && cat.y != p.y && !world->getContent(p)) return p;
  // }

  std::vector<Point2D> path = generatePath(world);
    // for (int i =2;i<path.size()+1; i++) {
    //   path.push_back(path[path.size()-i]);
    //   path.erase(std::next(path.begin(), i-1), std::next(path.begin(), i));
    // }
    std::unordered_map<Point2D, bool> blankVisitied;
    std::unordered_set<Point2D> blankFrontier;

  if (path.size() == 0) {


    std::vector<Point2D> neighbors = getVisitableNeightbors(world, world->getCat(), blankVisitied,blankFrontier);

    auto rand = Random::Range(0, neighbors.size()-1);

    std::cout << "Catcher picking random tile" << std::endl;

    return neighbors[rand];

  }

  std::vector<float> pathScore;

  for (auto point : path) {
    blankFrontier.insert(point);
  }

  for (auto point : path) {
    pathScore.push_back((4.0f-getVisitableNeightbors(world, point, blankVisitied, blankFrontier).size())/2.0f);
    //world->printPathfinding(blankVisitied, blankFrontier);

  }

  std::cout << "Scores: " << std::endl;
  for (int i =1; i <= pathScore.size(); i++) {
    std::cout << pathScore[pathScore.size() -i] << std::endl;
  }

 // world->printPathfinding(blankVisitied, blankFrontier);

  std::vector<Point2D> catNeig =getVisitableNeightbors(world, world->getCat(), blankVisitied, blankFrontier);
  std::vector<Point2D> backNeig =getVisitableNeightbors(world, catNeig.front(), blankVisitied, blankFrontier);
  std::vector<Point2D> frontNeig =getVisitableNeightbors(world, path[path.size()-1], blankVisitied, blankFrontier);


    if (backNeig.size() <= 1) {
      std::cout << "Check (front)" << std::endl;
      return path[path.size()-1];
    }
    if (frontNeig.size() == 0) {
      std::cout << "Check (front)" << std::endl;
      return catNeig.front();
    }
    if (catNeig.size() ==0) {
      std::cout << "Checkmate" << std::endl;
      return path[path.size()-1];
    }
    // if (frontNeig.size() == 0) {
    //   std::cout << "Check" << std::endl;
    //
    //   if (!backNeig.size() == 0){
    //     return catNeig.front();
    //   }
    // }

  for (int i =3; i <= pathScore.size(); i++) {//search through the path and its scores to find a suitable place to make the trap

    if (pathScore[pathScore.size()-i]+pathScore[pathScore.size()-(i-1)]+pathScore[pathScore.size()-(i-2)] > 6-(i)){

      std::cout << "Total score of "<< pathScore[pathScore.size()-i]+pathScore[pathScore.size()-(i-1)]+pathScore[pathScore.size()-(i-2)] << " is greater than 6-" << i << std::endl;

      std::vector<Point2D> candidates;

      for (int j = 0; j<2;j++) {
        std::vector<Point2D> neigs = getVisitableNeightbors(world, path[(pathScore.size()+1) - (i-j)], blankVisitied, blankFrontier);
        for (auto point : neigs) {
          candidates.push_back(point);
          blankVisitied[point] = true;
        }
      }
      world->printPathfinding(blankVisitied, blankFrontier);

      if (candidates.size() == 0) {break;}
      return candidates.front();
    }
  }

  return path[(path.size())/2];

}
