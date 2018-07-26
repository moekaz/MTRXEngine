/*
	Author: Mohamed Kazma
	Description: Implementation of a capsule collider
*/

#include "../headers/CapsuleCollider.h"
#include "../headers/BoxCollider.h"
#include "../headers/SphereCollider.h"
//#include "../headers/MeshCollider.h"

// Constructor
CapsuleCollider::CapsuleCollider(const glm::vec3& center , float radii , float height) : Collider(center)
{
	type = ColliderType::Capsule;
	this->height = height;
	A = center - glm::vec3(0, height / 2, 0);	// Center should be the midpoint of the height line segment of the capsule
	B = center + glm::vec3(0, height / 2, 0);
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
		case ColliderType::Sphere:
		{
			std::cout << "Capsule sphere collision detection" << std::endl;
			CapsuleCollider& collider = static_cast<CapsuleCollider&>(col);
			collision = CollisionUtil::CapsuleCapsuleCollision(A, B, collider.A, collider.B, radii, collider.radii);
			break;
		}
		case ColliderType::Box:
		{
			std::cout << "Capsule Box collision detection" << std::endl;
			BoxCollider& collider = static_cast<BoxCollider&>(col);
			std::vector<glm::vec3> axes = { collider.sideDirection , collider.upDirection , collider.forwardDirection };
			collision = CollisionUtil::BoxCapsuleCollision(collider.center, center, A, B, radii, collider.min, collider.max, axes, collider.halfExtents);
			break;
		}
		case ColliderType::Capsule:
		{
			std::cout << "Capsule capsule collision detection" << std::endl;
			CapsuleCollider& collider = static_cast<CapsuleCollider&>(col);
			collision = CollisionUtil::CapsuleCapsuleCollision(A , B , collider.A , collider.B , radii , collider.radii);
			break;
		}
		case ColliderType::Mesh:
		{
			std::cout << "Capsule Mesh collision detection" << std::endl;
			//CapsuleCollider& collider = static_cast<CapsuleCollider&>(col);
			//collision = CollisionUtil::CapsuleCapsuleCollision(A, B, collider.A, collider.B, radii, collider.radii);
			break;
		}
		default:
		{
			std::cout << "HOUSTON WE HAVE A PROBLEM" << std::endl;
			collision = false;
		}
	}

	UpdateCollisionInfo();	// Update the collision information such as when the collision occurred etc etc...

	return collision;
}

// Update values of the collider
void CapsuleCollider::Update(const glm::vec3& newCenter)
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

