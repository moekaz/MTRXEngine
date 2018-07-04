/*
	Author: Mohamed Kazma
	Description: Implementation of a box collider
*/

#include "../headers/BoxCollider.h"
#include "../headers/SphereCollider.h"
//#include "../headers/CapsuleCollider.h"
//#include "../headers/MeshCollider"

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

// Print the values of the box collider
std::ostream& operator<<(std::ostream& os, const BoxCollider&)
{

	return os;
}