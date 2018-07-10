/*
	Author: Mohamed Kazma
	Description: Implementation of a box collider
*/

#include "../headers/BoxCollider.h"
#include "../headers/SphereCollider.h"
//#include "../headers/CapsuleCollider.h"
//#include "../headers/MeshCollider"

/* Constructor */
BoxCollider::BoxCollider(const Vector3D& center) : ConvexShapeCollider(center)
{
	type = ColliderType::Box;
	halfExtents = Vector3D(0.5 , 0.5 , 0.5);	// The width along each axis should be 1 

	// Setup vertices and mins and maxes
	vertices =
	{
		new Vector3D(-0.5 , 0.5 , 0.5),
		new Vector3D(0.5 , 0.5 , 0.5),
		new Vector3D(-0.5 , -0.5 , 0.5),
		new Vector3D(0.5 , -0.5 , 0.5),
		new Vector3D(-0.5 , 0.5 , -0.5),
		new Vector3D(0.5 , 0.5 , -0.5),
		new Vector3D(-0.5 , -0.5 , -0.5),
		new Vector3D(0.5 , -0.5 , -0.5),
	};

	min = Vector3D(-0.5, -0.5, -0.5);	// Minimum positions
	max = Vector3D(0.5, 0.5, 0.5);	// Maximum positions
}

/* Destructor */
BoxCollider::~BoxCollider() {}

/* Functions */

// Update values of the collider
void BoxCollider::Update(Vector3D& center)
{
	this->center = center;
	//RecomputeMinsMaxes();		// Depends on how we are storing transformations

	//Calculate half extents if changed (IF THE SCALE CHANGES)
	//halfExtents.x *= localScale.x;
	//halfExtents.y *= localScale.y;
	//halfExtents.z *= localScale.z;
}

// Gives us whether there is a collision occurring
bool BoxCollider::CheckCollision(Collider& col)
{
	UpdateCollisionInfo();
	return false;
}

// Recalculate the mins and maxes again
void BoxCollider::RecomputeMinsMaxes()
{
	min = *vertices[0];
	max = *vertices[0];

	for (int i = 0; i < vertices.size(); i++)
	{
		min.x = min.x > vertices[i]->x ? vertices[i]->x : min.x;
		min.y = min.y > vertices[i]->y ? vertices[i]->y : min.y;
		min.z = min.z > vertices[i]->z ? vertices[i]->z : min.z;

		max.x = max.x < vertices[i]->x ? vertices[i]->x : max.x;
		max.y = max.y < vertices[i]->y ? vertices[i]->y : max.y;
		max.x = max.z < vertices[i]->z ? vertices[i]->z : max.z;
	}
}

// Print the values of the box collider
std::ostream& operator<<(std::ostream& os, const BoxCollider&)
{

	return os;
}