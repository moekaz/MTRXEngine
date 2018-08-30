/*
	Author: Mohamed Kazma
	Description: Colliders with a convex shape (We can use SAT for collision with these shapes)
*/

#pragma once
#ifndef CONVEXSHAPECOLLIDER_H
#define CONVEXSHAPECOLLIDER_H

#include <vector>
#include <glm/vec3.hpp>

#include "Collider.h"
#include "CollisionUtil.h"

class ConvexShapeCollider : public Collider
{
public:
	ConvexShapeCollider(const glm::vec3& = glm::vec3());			// Constructor
	~ConvexShapeCollider();											// Destructor

	glm::vec3 Support(ConvexShapeCollider& , glm::vec3&);			// Support is used to build a simplex as it will return a point on the minkowski sum (or difference depending on naming) 
	glm::vec3& FarthestPointInDirection(glm::vec3&);				// Farthest point within a certain direction

	bool CheckCollision(Collider&);								    // Does collision detection checks
	virtual bool RaycastCollision(Ray&);							// Raycast collision
    virtual void Update(const glm::vec3&);							// Updates the values of the collider

private:
protected:
};
#endif // !CONVEXSHAPECOLLIDER_H
