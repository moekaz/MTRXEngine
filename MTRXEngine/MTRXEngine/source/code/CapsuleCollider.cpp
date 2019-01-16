/*
	Author: Mohamed Kazma
	Description: Implementation of a capsule collider
*/

#include <PrecompiledHeader.h>

#include <CapsuleCollider.h>
#include <BoxCollider.h>
#include <SphereCollider.h>

namespace MTRX
{
	// Constructor
	CapsuleCollider::CapsuleCollider(const glm::vec3& center, float radii, float height) : Collider(ColliderType::Capsule, center),
		height(height), A(center - glm::vec3(0, height / 2, 0)), B(center - glm::vec3(0, height / 2, 0)), radii(radii)
	{
	}

	// Destructor
	CapsuleCollider::~CapsuleCollider() {}

	// Checks for collisions
	bool CapsuleCollider::CheckCollision(const Collider& col)
	{
		bool collision = false;

		switch (col.type)
		{
		case ColliderType::Sphere:
		{
			std::cout << "Capsule sphere collision detection" << std::endl;
			const CapsuleCollider& collider = static_cast<const CapsuleCollider&>(col);
			collision = CollisionUtil::CapsuleCapsuleCollision(A, B, collider.A, collider.B, radii, collider.radii);
			break;
		}
		case ColliderType::Box:
		{
			std::cout << "Capsule Box collision detection" << std::endl;
			const BoxCollider& collider = static_cast<const BoxCollider&>(col);
			collision = CollisionUtil::BoxCapsuleCollision(collider.GetPosition(), center, A, B, radii, collider.min, collider.max, collider.GetAxes(), collider.halfExtents);
			break;
		}
		case ColliderType::Capsule:
		{
			std::cout << "Capsule capsule collision detection" << std::endl;
			const CapsuleCollider& collider = static_cast<const CapsuleCollider&>(col);
			collision = CollisionUtil::CapsuleCapsuleCollision(A, B, collider.A, collider.B, radii, collider.radii);
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

	// Raycast collision with capsule
	bool CapsuleCollider::RaycastCollision(const Ray& ray)
	{
		return CollisionUtil::RayCapsuleCollision(ray.startPosition, ray.direction, A, B, radii);
	}

	// Update values of the collider
	void CapsuleCollider::PhysicsUpdate()
	{
	}

	// Print out the values of the collider
	std::ostream& operator<<(std::ostream& os, const CapsuleCollider& caps)
	{
		return os << "Capsule Collider:" << std::endl
			<< "-----------------" << std::endl
			<< "Center: " << std::endl
			<< "x: " << caps.center.x << std::endl
			<< "y: " << caps.center.y << std::endl
			<< "z: " << caps.center.z << std::endl
			<< "Radii: " << caps.radii << std::endl
			<< "Height: " << caps.height;
	}
}