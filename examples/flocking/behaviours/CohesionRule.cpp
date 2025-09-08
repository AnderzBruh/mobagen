#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce = Vector2f::zero();

  // todo: add your code here to make a force towards the center of mass
  // hint: iterate over the neighborhood

  // find center of mass

    bool nearEnemy = false;


  if (neighborhood.size() > 0) {

    for (Boid* neighbor : neighborhood) {

      if (!neighbor->getIfEnemy()) // ignores coheding with enemies and flags it if it sees one
      {
        cohesionForce += neighbor->getPosition();
      } else 
      {
        nearEnemy = true;
      }

    }
    cohesionForce /= neighborhood.size();

    cohesionForce -= boid->getPosition();

  }

  if (boid->getIfEnemy()) { // so the enemy does not slow down as it gets closer to its target, multiplied so it gives more "chase"
    cohesionForce = cohesionForce.normalized() * 500;
  }

  if (nearEnemy) { //if it gets scared it will ignore it's local flock so it can run away
    cohesionForce = Vector2f::zero();
  }

  return cohesionForce;
}