#include "Agent.h"
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

  while (!frontierSet.empty()) {
   // cout << "looked at frontier" << endl;
  //  w->printPathfinding(visited,frontierSet);

    Point2D current = frontier.front();// get the current from frontier

    frontier.pop();
    frontierSet.erase(current);// remove the current from frontierset
    visited[current] = true;// mark current as visited
    std::vector<Point2D> visitables =  getVisitableNeightbors(w, current, visited, frontierSet); // returns a vector of neighbors that are not visited, not cat, not block, not in the queue
   // cout << "got visitables: " << visitables.size() <<endl;
   // cout << "frontier count: " << frontier.size() << endl;


    for (auto visitable : visitables) {// iterate over the neighs:
     // cout << "looked at visitable" << endl;

       cameFrom[visitable] = current;   // for every neighbor set the cameFrom
      frontier.push(visitable);
       frontierSet.insert(visitable);// enqueue the neighbors to frontier and frontierset
    }
   // cout << w->catWinsOnSpace(current) << endl;


    if (w->catWinsOnSpace(current)){borderExit = current; break;}// do this up to find a visitable border and break the loop
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

  }
  // if there isnt a reachable border, just return empty vector
  // if your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move
  return path;
}

std::vector<Point2D> Agent::getVisitableNeightbors(World* w, Point2D current, unordered_map<Point2D, bool> visited, unordered_set<Point2D> frontier)
{

  std::vector<Point2D> visitables;
  for (auto neighbor : w->neighbors(current)) {
    if (w->isValidPosition(neighbor) && !w->getContent(neighbor) && !visited.contains(neighbor) && !frontier.contains(neighbor) && neighbor != w->getCat()){visitables.push_back(neighbor);}

  }

  return visitables;
}