#include "BoundedAreaRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"
#include <iostream>


Vector2f BoundedAreaRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Return a force proportional to the proximity of the boids with the bounds, and opposed to it
  Vector2f force = Vector2f::zero();  // zero

  // todo: add here your code code here do make the boid follow the bounded box rule
  // hint: use this->world->engine->window->size() and desiredDistance

  float Xdist = fmaxf(
     ((this->world->engine->window->size().x / 2) - desiredDistance) - abs(boid->getPosition().x - (this->world->engine->window->size().x / 2)), 0.01);
  float Ydist = fmaxf(
      ((this->world->engine->window->size().y / 2) - desiredDistance) - abs(boid->getPosition().y - (this->world->engine->window->size().y / 2)), 0.01);

  

  if (Xdist < 1 || Ydist < 1) 
  {
   // std::cout << Xdist << "," << Ydist <<  std::endl;
    force = (Vector2f(this->world->engine->window->size().x / 2, this->world->engine->window->size().y / 2) - boid->getPosition());
    force.x /= Xdist;
    force.y /= Ydist;
    force *= 9999999;
  }
  //std::cout << boid->getPosition().x << "," << boid->getPosition().y << std::endl;


  return force * weight;
}

bool BoundedAreaRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  auto size = this->world->engine->window->size();
  auto widthWindows = size.x;
  auto heightWindows = size.y;
  bool valueHasChanged = false;

  // We cap the max separation as the third of the min of the width.height
  auto minHeightWidth = std::min(widthWindows, heightWindows);

  if (ImGui::SliderInt("Desired Distance From Borders", &desiredDistance, 0.0f, (int)(minHeightWidth / 3), "%i")) {
    valueHasChanged = true;
  }

  return valueHasChanged;
}

void BoundedAreaRule::draw(const Boid& boid, SDL_Renderer* renderer) const {
  FlockingRule::draw(boid, renderer);
  auto size = this->world->engine->window->size();
  auto dist = (float)desiredDistance;

  // Draw a rectangle on the map
  Polygon::DrawLine(renderer, Vector2f(dist, dist), Vector2f(size.x - dist, dist), Color::Gray);                    // TOP
  Polygon::DrawLine(renderer, Vector2f(size.x - dist, dist), Vector2f(size.x - dist, size.y - dist), Color::Gray);  // RIGHT
  Polygon::DrawLine(renderer, Vector2f(size.x - dist, size.y - dist), Vector2f(dist, size.y - dist), Color::Gray);  // Bottom
  Polygon::DrawLine(renderer, Vector2f(dist, size.y - dist), Vector2f(dist, dist), Color::Gray);                    // LEFT
}