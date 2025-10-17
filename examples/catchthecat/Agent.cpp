#include "Agent.h"
#include "World.h"
#include "datastructures/Vector.h"
using namespace std;
std::vector<Point2D> Agent::generatePath(World* w, bool useWeights) {
  unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path
  vector<Point2D> frontier;                   // to store next ones to visit
  unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element dont exist [] will give you wrong results
  unordered_map<Point2D,float> weights;
  // bootstrap state
  auto catPos = w->getCat();
  frontier.push_back(catPos);
  frontierSet.insert(catPos);
  weights[catPos] = 0;
  Point2D borderExit = Point2D::INFINITE;  // if at the end of the loop we dont find a border, we have to return random points

  while (!frontierSet.empty()) {
   // cout << "looked at frontier" << endl;

    Point2D current = frontier.back();// get the current from frontier

    frontier.pop_back();
    frontierSet.erase(current);// remove the current from frontierset
    visited[current] = true;// mark current as visited
   // cout << "got visitables: " << visitables.size() <<endl;
   // cout << "frontier count: " << frontier.size() << endl;

    std::vector<Point2D> visitables =  getVisitableNeightbors(w, current, visited, frontierSet); // returns a vector of neighbors that are not visited, not cat, not block, not in the queue

    for (auto visitable : visitables) {// iterate over the neighs:
     // cout << "looking at: " << visitable.x << "," << visitable.y << endl;
       cameFrom[visitable] = current;



    if (useWeights) {

      std::unordered_map<Point2D, bool> blankVisitied;
      std::unordered_set<Point2D> blankFrontier;
      weights[visitable] = weights[current] + (6-getVisitableNeightbors(w, current, blankVisitied, blankFrontier).size()) * 0.5f + 1;// for every neighbor set the cameFrom
      if (w->catWinsOnSpace(visitable)){weights[visitable] += 6.5f* ((w->getWorldSideSize()*2.0f) / (abs(visitable.x) + abs(visitable.y))) ;}

     // cout << "using weight" << endl;
      for (int i = 0; i < frontier.size(); i++) {
        if (weights[frontier[i]] <= weights[visitable]) {
          frontier.insert(frontier.begin() + (i), visitable);
         //  cout << "placed into frontier at: " << i << endl;
          break;
        };

        if ( i == frontier.size() - 1 ) {
         //  cout << "placed last into frontier" << endl;

          frontier.insert(frontier.begin(), visitable);
          break;
        }
      }

      if (frontier.size() == 0){
       //  cout << "placed first into frontier" << endl;
        frontier.insert(frontier.begin(), visitable);

      }
      //cout << "done using weight" << endl;
    }else{
      frontier.insert(frontier.begin(), visitable);
    }

       frontierSet.insert(visitable);// enqueue the neighbors to frontier and frontierset
    }
   // cout << w->catWinsOnSpace(current) << endl;


    if (w->catWinsOnSpace(current)) {
      if (useWeights){w->printPathfindingWeights(weights);}
      borderExit = current;
      break;
    }// do this up to find a visitable border and break the loop

   // cout << "weights" << endl;
   // w->printPathfindingWeights(weights);
  //  cout << "frontier" << endl;

   // w->printPathfinding(visited,frontierSet);

  }



 // cout << "found an exit" << endl;

  std::vector<Point2D> path;
  if (borderExit != Point2D::INFINITE) {    // if the border is not infinity, build the path from border to the cat using the camefrom map
   // cout << "found an exit" << endl;
    Point2D current = borderExit;
    while (current != catPos) {
      path.push_back(current);
      current = cameFrom[current];
    }

  }else {

  }
  // if there isnt a reachable border, just return empty vector
  // if your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move
  return path;
}

std::vector<Point2D> Agent::getVisitableNeightbors(World* w, Point2D current, unordered_map<Point2D, bool> visitedMap, unordered_set<Point2D> frontierSet)
{

  std::vector<Point2D> visitables;
  for (auto neighbor : w->neighbors(current)) {
    if (w->isValidPosition(neighbor) && !w->getContent(neighbor) && !visitedMap.contains(neighbor) && !frontierSet.contains(neighbor) && neighbor != w->getCat()){visitables.push_back(neighbor);}

  }

  return visitables;
}
