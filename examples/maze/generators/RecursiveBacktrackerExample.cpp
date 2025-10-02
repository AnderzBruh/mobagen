#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>
bool RecursiveBacktrackerExample::Step(World* w) {

  if (stack.size() > 0) {
    Point2D nowPoint = stack[stack.size()-1];

    w->SetNodeColor(nowPoint,Color32(255,0,0,255));
   // w->SetWest(nowPoint + Point2D(1,0),false);

    std::vector<Point2D> visitables = getVisitables(w, nowPoint);

    //std::cout << visitables.size() << std::endl;

    for (auto visitable : visitables) {
    //  w->SetNodeColor(visitable,Color32(255,255,0,255));

    }

    if (visitables.size() > 0) {

      Point2D nextPoint = visitables[rand() % visitables.size()];
      visited[nextPoint.x][nextPoint.y] = false;
      stack.push_back(nextPoint);

      Point2D offset =  nowPoint - nextPoint;

      if (offset == Point2D(1,0)){w->SetWest(nowPoint,false); std::cout << "Removed West Wall" << std::endl;}
      if (offset == Point2D(-1,0)){w->SetEast(nowPoint,false); std::cout << "Removed East Wall" << std::endl;}
      if (offset == Point2D(0,1)){w->SetNorth(nowPoint,false); std::cout << "Removed North Wall" << std::endl;}
      if (offset == Point2D(0,-1)){w->SetSouth(nowPoint,false); std::cout << "Removed South Wall" << std::endl;}


    }else {
     // stack.insert(stack.begin(),stack[stack.size()-1]);
      stack.pop_back();
      w->SetNodeColor(nowPoint,Color32(0,0,0,255));

    }

  }else {

    Point2D newPoint = randomStartPoint(w);

    std::cout << "Added random start point: " << newPoint.x << "," << newPoint.y << std::endl;

    stack.push_back(newPoint);
    visited[newPoint.x][newPoint.y] = true;

  //  return false;
  }
  // todo: implement this
  return true;
}

void RecursiveBacktrackerExample::Clear(World* world) {
  visited.clear();
  stack.clear();
  auto sideOver2 = world->GetSize() / 2;

  for (int i = -sideOver2; i <= sideOver2; i++) {
    for (int j = -sideOver2; j <= sideOver2; j++) {
      visited[i][j] = true;
    }
  }
}

Point2D RecursiveBacktrackerExample::randomStartPoint(World* world) {
  auto sideOver2 = world->GetSize() / 2;

  // todo: change this if you want
  for (int y = -sideOver2; y <= sideOver2; y++)
    for (int x = -sideOver2; x <= sideOver2; x++)
      if (!visited[y][x]) return {x, y};
  return {INT_MAX, INT_MAX};
}

std::vector<Point2D> RecursiveBacktrackerExample::getVisitables(World* w, const Point2D& p) {
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> visitables;

  // todo: implement this


  if (p.y < sideOver2 && visited[p.x][p.y+1] == false){visitables.push_back(p + Point2D(0,1));}
  if (p.x < sideOver2 && visited[p.x+1][p.y] == false){visitables.push_back(p + Point2D(1,0));}
  if (p.y > -sideOver2 && visited[p.x][p.y-1] == false){visitables.push_back(p + Point2D(0,-1));}
  if (p.x > -sideOver2 && visited[p.x-1][p.y] == false){visitables.push_back(p + Point2D(-1,0));}

  std::cout << "Num can visit: " << visitables.size() << std::endl;

  return visitables;
}
