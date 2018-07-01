/*
	Author: mohamed kazma
	Description: Header file for a sphere collider
*/

#ifndef SPHERECOLLIDER_H
#define SPHERECOLLIDER_H

#include <iostream>

#include "Vector3D.h"
#include "Collider.h"
#include "BoxCollider.h"
//#include "CapsuleCollider.h"
//#include "MeshCollider.h"

class SphereCollider : public Collider
{
public:
	float radius;																	// Radius of a sphere collider

	SphereCollider(const Vector3D& vec = Vector3D::zero, float radius = 1);			// Constructor 
	~SphereCollider();																// Destructor

	void Update(const Vector3D&);													// Update collider values
	friend std::ostream& operator<<(std::ostream& , const SphereCollider&);			// Print out values of the collider

private:
protected:
	bool SphereCollision(Collider&);												// Sphere sphere collision detection
	bool BoxCollision(Collider&);													// Sphere box collision detection
	bool CapsuleCollision(Collider&);												// Sphere capsule collision detection
	bool MeshCollision(Collider&);													// Sphere Mesh collision detection
};
#endif // SPHERECOLLIDER_H