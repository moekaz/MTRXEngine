/*
	Author: Mohamed Kazma
	Description: Implementation of a capsule collider
*/

#include "../headers/CapsuleCollider.h"

// Constructor
CapsuleCollider::CapsuleCollider(Vector3D& center , float radii , float height) : Collider(center)
{
	type = ColliderType::Capsule;
	this->height = height;
	A = center - Vector3D(0, height / 2, 0);	// Center should be the midpoint of the height line segment of the capsule
	B = center + Vector3D(0, height / 2, 0);
	this->radii = radii;
}

// Destructor
CapsuleCollider::~CapsuleCollider() {}

// Checks for collisions
bool CapsuleCollider::CheckCollision(Collider& col)
{
	bool collision = false;

	switch (col.type)
	{
		case ColliderType::Capsule:
		{
			CapsuleCollider& collider = static_cast<CapsuleCollider&>(col);
			collision = CollisionUtil::CapsuleCapsuleCollision(*this , collider);
		}
		case ColliderType::Box:
		{
			//collision=
		}
		case ColliderType::Mesh:
		{
			//collision=
		}
		case ColliderType::Sphere:
		{
			//collision
		}
	}

	UpdateCollisionInfo();

	return collision;
}

// Update values of the collider
void CapsuleCollider::Update(const Vector3D& newCenter)
{
	center = newCenter;
}

// Print out the values of the collider
std::ostream& operator<<(std::ostream& os , const CapsuleCollider& caps)
{
	os << "Capsule Collider:" << std::endl
		<< "-----------------" << std::endl
		<< "Center: " << caps.center << std::endl
		<< "Radii: " << caps.radii << std::endl
		<< "Height: " << caps.height;

	return os;
}

