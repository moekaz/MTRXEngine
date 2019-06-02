/*
	Author: Mohamed Kazma
	Description: Implementation of a capsule collider
*/

#include <PrecompiledHeader.h>

#include <colliders/CapsuleCollider.h>
#include <colliders/BoxCollider.h>
#include <colliders/SphereCollider.h>

namespace mtrx
{
	// Constructor
	CapsuleCollider::CapsuleCollider(const glm::vec3& center, float radii, float height) : Collider(ColliderType::Capsule, center),
		height(height), A(center - glm::vec3(0, height / 2, 0)), B(center - glm::vec3(0, height / 2, 0)), radii(radii)
	{}

	CapsuleCollider::CapsuleCollider(const CapsuleCollider& collider1, const CapsuleCollider& collider2) : Collider(ColliderType::Capsule)
	{
		// Create a bounding capsule
		// Dunno if i want to do that 
	}

	// Destructor
	CapsuleCollider::~CapsuleCollider() 
	{}

	// Checks for collisions
	bool CapsuleCollider::CheckCollision(const Collider& col)
	{
		bool collision = false;
		switch (col.GetColliderType())
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
				collision = CollisionUtil::BoxCapsuleCollision(collider.GetPosition(), center, A, B, radii, collider.GetAxes(), collider.halfExtents);
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
				break;
			}
			default:
			{
				std::cout << "HOUSTON WE HAVE A PROBLEM" << std::endl;
				collision = false;
			}
		}

		return collision;
	}

	// Raycast collision with capsule
	bool CapsuleCollider::RaycastCollision(const Ray& ray)
	{
		return CollisionUtil::RayCapsuleCollision(ray.startPosition, ray.direction, A, B, radii);
	}

	float CapsuleCollider::GetSize()
	{
		return 0.f;
	}

	float CapsuleCollider::GetGrowth(const CapsuleCollider& capsuleCollider)
	{
		return 0.f;
	}
}