/*
	Author: Mohamed Kazma
	Description: Colliders with a convex shape (We can use SAT for collision with these shapes)
*/

#pragma once
#ifndef CONVEXSHAPECOLLIDER_H
#define CONVEXSHAPECOLLIDER_H

#include <vector>

#include "Vector3D.h"
#include "Collider.h"
#include "CollisionUtil.h"

class ConvexShapeCollider : public Collider
{
public:
	std::vector<Vector3D*> vertices;								// Store the vertices of the collider
	std::vector<Vector3D*> edges;									// Store the edges of the collider

	ConvexShapeCollider(const Vector3D& = Vector3D::zero);			// Constructor
	~ConvexShapeCollider();											// Destructor

	Vector3D& Support(ConvexShapeCollider& , Vector3D&);			// Support is used to build a simplex as it will return a point on the minkowski sum (or difference depending on naming) 
	Vector3D& FarthestPointInDirection(Vector3D&);					// Farthest point within a certain direction

	bool CheckCollision(Collider&);								    // Does collision detection checks
    virtual void Update(const Vector3D&);							// Updates the values of the collider

private:
protected:
};
#endif // !CONVEXSHAPECOLLIDER_H
