#include "AlignmentRule.h"
#include "../gameobjects/Boid.h"

Vector2f AlignmentRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to match the heading of neighbors = Average velocity
  Vector2f averageVelocity = boid->getVelocity();

  // todo: add your code here to align each boid in a neighborhood
  // hint: iterate over the neighborhood

  bool nearEnemy = false;
  
    if(!boid->getIfEnemy()){ // only aligns if it is not an enemy

        for (Boid* neighbor : neighborhood) {// ignores aligning with enemies and flags it if it sees one
          if (!neighbor->getIfEnemy()) {
            averageVelocity += neighbor->getVelocity();
          } 
          else 
          {
            nearEnemy = true;
          }
        }

        averageVelocity /= neighborhood.size() + 1;
    }

    if (nearEnemy) { //if it gets scared it will ignore it's local flock so it can run away
      averageVelocity = Vector2f::zero();
    }

  return averageVelocity * weight;
}