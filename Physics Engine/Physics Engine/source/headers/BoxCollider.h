/*
	Author: Mohamed Kazma
	Description: An implementation of a box collider
*/

#pragma once
#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include <iostream>

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
	Vector3D min;															// Stores min x,y,z
	Vector3D max;															// Stores max x,y,z
	Vector3D halfExtents;													// Half widths along each axis

	BoxCollider(const Vector3D& = Vector3D::zero);							// Constructor
	~BoxCollider();															// Destrutor

	void Update(Vector3D&);													// Update the values of the collider
	bool CheckCollision(Collider&);											// Check collision with box collider 
	void RecomputeMinsMaxes();												// Recalculates the min and max values of the vertices 

	friend std::ostream& operator<<(std::ostream& os , const BoxCollider&);	// Print out the values of th collider

private:
protected:
};
#endif // BOXCOLLIDER_H
