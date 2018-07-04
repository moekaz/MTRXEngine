/*
	Author: mohamed kazma
	Description: Header file for a sphere collider
*/

#ifndef SPHERECOLLIDER_H
#define SPHERECOLLIDER_H

#include <iostream>

#include "Vector3D.h"
#include "Collider.h"
#include "CollisionUtil.h"

// Forward declarations
class BoxCollider;
class CapsulesCollider;
class MeshCollider;

class SphereCollider : public Collider
{
public:
	float radius;																	// Radius of a sphere collider

	SphereCollider(const Vector3D& vec = Vector3D::zero, float radius = 1);			// Constructor 
	~SphereCollider();																// Destructor

	void Update(const Vector3D&);													// Update collider values
	bool CheckCollision(Collider&);													// Sphere collision detection

	friend std::ostream& operator<<(std::ostream&, const SphereCollider&);			// Print out values of the collider

private:
protected:
};
#endif // SPHERECOLLIDER_H