#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>
bool RecursiveBacktrackerExample::Step(World* w) {

  // add the first one if it hasn't started yet

  if (stack.size() == 0) {
    if (visited.size()>0) {return false;}

    Point2D newPoint = randomStartPoint(w);
    stack.push_back(newPoint);

    //if the first one in the stack has been visited then we know it's at the end because it will only check this twice, once at the beginning and once at the end
    std::cout << "Added random start point: " << newPoint.x << "," << newPoint.y << std::endl;
    visited.contains(newPoint.y * w->GetSize() + newPoint.x);
  }

  // get the last element in the stack and find its neighbors
  Point2D nowPoint = stack[stack.size()-1];
  w->SetNodeColor(nowPoint,Color32(255,0,0,255));
  std::vector<Point2D> visitables = getVisitables(w, nowPoint);

  if (visitables.size() > 0) {

    // gets a random neighbor and adds it to the stack
    Point2D nextPoint = visitables[rand() % visitables.size()];
    visited.insert( nextPoint.y * w->GetSize() + nextPoint.x);
    stack.push_back(nextPoint);

    // this removes the wall between this and the next cell
    Point2D offset =  nowPoint - nextPoint;
    if (offset == Point2D(1,0)){w->SetWest(nowPoint,false); std::cout << "Removed West Wall" << std::endl;}
    if (offset == Point2D(-1,0)){w->SetEast(nowPoint,false); std::cout << "Removed East Wall" << std::endl;}
    if (offset == Point2D(0,1)){w->SetNorth(nowPoint,false); std::cout << "Removed North Wall" << std::endl;}
    if (offset == Point2D(0,-1)){w->SetSouth(nowPoint,false); std::cout << "Removed South Wall" << std::endl;}
  }
  else {
   // Backtrack by deleting the last one
    stack.pop_back();
    w->SetNodeColor(nowPoint,Color32(0,0,0,255));
  }

  return true;
}

void RecursiveBacktrackerExample::Clear(World* world) {
  visited.clear();
  stack.clear();
  visited.clear();
}

Point2D RecursiveBacktrackerExample::randomStartPoint(World* world) {
  auto sideOver2 = world->GetSize() / 2;

  // todo: change this if you want
  for (int y = -sideOver2; y <= sideOver2; y++)
    for (int x = -sideOver2; x <= sideOver2; x++)
      if (visited.contains(y*world->GetSize()+x)) return {x, y};
  return {INT_MAX, INT_MAX};
}

std::vector<Point2D> RecursiveBacktrackerExample::getVisitables(World* w, const Point2D& p) {
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> visitables;

  // todo: implement this


  if (p.y <  sideOver2 && !visited.contains( p.x    + (p.y+1)*w->GetSize())){visitables.push_back(p + Point2D(0,1));}
  if (p.x <  sideOver2 && !visited.contains((p.x+1) +  p.y   *w->GetSize())){visitables.push_back(p + Point2D(1,0));}
  if (p.y > -sideOver2 && !visited.contains( p.x    + (p.y-1)*w->GetSize())){visitables.push_back(p + Point2D(0,-1));}
  if (p.x > -sideOver2 && !visited.contains((p.x-1) +  p.y   *w->GetSize())){visitables.push_back(p + Point2D(-1,0));}

  std::cout << "Num can visit: " << visitables.size() << std::endl;

  return visitables;
}
