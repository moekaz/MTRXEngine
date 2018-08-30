/*
	Author: Mohamed Kazma
	Description: An implementation of a box collider
*/

#pragma once
#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include <iostream>
#include <glm/vec3.hpp>

#include "Vector3D.h"
#include "ConvexShapeCollider.h"
#include "CollisionUtil.h"

// Forward declarations
class SphereCollider;
class CapsuleCollider;
class MeshCollider;

class BoxCollider : public ConvexShapeCollider
{
public:
	glm::vec3 min;															// Stores min x,y,z
	glm::vec3 max;															// Stores max x,y,z
	glm::vec3 halfExtents;													// Half widths along each axis
	glm::vec3* axes[3];														// Store the axes of the box collider

	BoxCollider(const glm::vec3& = glm::vec3());							// Constructor
	~BoxCollider();															// Destrutor

	void Update(const glm::vec3&);											// Update the values of the collider
	bool CheckCollision(Collider&);											// Check collision with box collider 
	bool RaycastCollision(Ray&);											// Raycast collision
	void RecomputeMinsMaxes();												// Recalculates the min and max values of the vertices 

	friend std::ostream& operator<<(std::ostream& os , const BoxCollider&);	// Print out the values of th collider

private:
protected:
};
#endif // BOXCOLLIDER_H
