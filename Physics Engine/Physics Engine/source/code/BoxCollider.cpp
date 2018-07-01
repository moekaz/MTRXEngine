/*
	Author: Mohamed Kazma
	Description: Implementation of a box collider
*/

#include "../headers/BoxCollider.h"

/* Constructor */
BoxCollider::BoxCollider(const Vector3D& center) : Collider(center)
{
	type = ColliderType::Box;
}

/* Destructor */
BoxCollider::~BoxCollider() {}

/* Functions */

// Update values of the collider
void BoxCollider::Update()
{
}

// Gives us whether there is a collision occurring
bool BoxCollider::CheckCollision()
{
	return false;
}
