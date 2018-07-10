/*
	Author: Mohamed Kazma
	Description: Capsule colliders
*/

#pragma once
#ifndef CAPSULECOLLIDER_H
#define CAPSULECOLLIDER_H

#include <iostream>

#include "Defs.h"
#include "Collider.h"
#include "CollisionUtil.h"

class CapsuleCollider: public Collider
{
public:
	float radii;																		// radii of the 2 spheres of the capsule
	Vector3D A;																			// Center of the first sphere													
	Vector3D B;																			// Center of the second sphere
	float height;																		// Height of the capsule

	CapsuleCollider(Vector3D& = Vector3D::zero , float = 0.25f , float = 0.5f);			// Constructor
	~CapsuleCollider();																	// Destructor

	bool CheckCollision(Collider&);														// Function for checking collision
	void Update(const Vector3D&);																// Updating the values of the collider

	friend std::ostream& operator<<(std::ostream&, const CapsuleCollider&);				// Print out the values of the collider

private:
protected:
};
#endif // !CAPSULECOLLIDER_H
