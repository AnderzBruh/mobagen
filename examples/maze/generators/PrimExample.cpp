#include "PrimExample.h"
#include "../World.h"
#include "Random.h"

bool PrimExample::Step(World* w) {
  int sideOver2 = w->GetSize() / 2;

  Point2D thisPoint;
  if (toBeVisited.size() == 0) {
    thisPoint = Point2D(0,0);

  }else {
    thisPoint = toBeVisited[rand() * toBeVisited.size()];
  }
  w->SetNodeColor(thisPoint,Color32(0,0,255,255));

  std::vector<Point2D> visitables = getVisitables(w,thisPoint);

  for (auto point : visitables) {
    w->SetNodeColor(point,Color32(255,255,0,255));
  }

  return true;
}
void PrimExample::Clear(World* world) {
  toBeVisited.clear();
  initialized = false;
}

std::vector<Point2D> PrimExample::getVisitables(World* w, const Point2D& p) {
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> visitables;
  auto clearColor = Color::DarkGray;

  if (p.y <  sideOver2 && isVisitable(w,p + Point2D(0, 1))){visitables.push_back(p + Point2D(0,1));}
  if (p.x <  sideOver2 && isVisitable(w,p + Point2D(1, 0))){visitables.push_back(p + Point2D(1,0));}
  if (p.y > -sideOver2 && isVisitable(w,p + Point2D(0, -1))){visitables.push_back(p + Point2D(0,-1));}
  if (p.x > -sideOver2 && isVisitable(w,p + Point2D(-1, 0))){visitables.push_back(p + Point2D(-1,0));}

  return visitables;
}

bool PrimExample::isVisitable(World* w, const Point2D& p) {
return w->GetNorth(p) && w->GetEast(p) && w->GetSouth(p) && w->GetWest(p);
}


std::vector<Point2D> PrimExample::getVisitedNeighbors(World* w, const Point2D& p) {
  std::vector<Point2D> deltas = {Point2D::UP, Point2D::DOWN, Point2D::LEFT, Point2D::RIGHT};
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> neighbors;

  // todo: code this

  return neighbors;
}
