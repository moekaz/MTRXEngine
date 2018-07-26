/*
	Author: Mohamed Kazma
	Description: Capsule colliders
*/

#pragma once
#ifndef CAPSULECOLLIDER_H
#define CAPSULECOLLIDER_H

#include <iostream>
#include <glm/vec3.hpp>

#include "Defs.h"
#include "Collider.h"
#include "CollisionUtil.h"

class CapsuleCollider: public Collider
{
public:
	float radii;																		// radii of the 2 spheres of the capsule
	glm::vec3 A;																			// Center of the first sphere													
	glm::vec3 B;																			// Center of the second sphere
	float height;																		// Height of the capsule

	CapsuleCollider(const glm::vec3& = glm::vec3() , float = 0.25f , float = 0.5f);			// Constructor
	~CapsuleCollider();																	// Destructor

	bool CheckCollision(Collider&);														// Function for checking collision
	void Update(const glm::vec3&);																// Updating the values of the collider

	friend std::ostream& operator<<(std::ostream&, const CapsuleCollider&);				// Print out the values of the collider

private:
protected:
};
#endif // !CAPSULECOLLIDER_H
