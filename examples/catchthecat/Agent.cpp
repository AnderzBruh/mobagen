#include "Agent.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "World.h"
#include "datastructures/Vector.h"
using namespace std;
std::vector<Point2D> Agent::generatePath(World* w) {
  unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path
  queue<Point2D> frontier;                   // to store next ones to visit
  unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element dont exist [] will give you wrong results

  // bootstrap state
  auto catPos = w->getCat();
  frontier.push(catPos);
  frontierSet.insert(catPos);
  Point2D borderExit = Point2D::INFINITE;  // if at the end of the loop we dont find a border, we have to return random points

  while (!frontier.empty()) {
    Point2D current = frontier.front();// get the current from frontier
    frontier.pop();// remove the current from frontierset
    visited[current] = true;// mark current as visited
    std::vector<Point2D> visitables =  getVisitableNeightbors(w, current); // returns a vector of neighbors that are not visited, not cat, not block, not in the queue
    for (auto visitable : visitables) {// iterate over the neighs:
       cameFrom[visitable] = current;   // for every neighbor set the cameFrom
       frontier.push(visitable);// enqueue the neighbors to frontier and frontierset
        frontierSet.insert(visitable);
    }
    if (w->catWinsOnSpace(current)){borderExit = current; break;}// do this up to find a visitable border and break the loop
  }

  std::vector<Point2D> path;
  if (borderExit != Point2D::INFINITE) {    // if the border is not infinity, build the path from border to the cat using the camefrom map
    cout << "found an exit" << endl;
    Point2D current = borderExit;
    while (cameFrom[current] != catPos) {
      path.push_back(current);
      current = cameFrom[current];
    }

  }
  // if there isnt a reachable border, just return empty vector
  // if your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move
  return path;
}

std::vector<Point2D> Agent::getVisitableNeightbors(World* w, Point2D current)
{
  std::vector<Point2D> visitables;
  for (auto neighbor : w->neighbors(current)) {
    if (w->catCanMoveToPosition(current)){visitables.push_back(neighbor);}
  }
  return visitables;
}