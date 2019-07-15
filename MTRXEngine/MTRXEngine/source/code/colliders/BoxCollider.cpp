/*
	Author: Mohamed Kazma
	Description: Implementation of a box collider
*/

#include <PrecompiledHeader.h>
#include <colliders/BoxCollider.h>
#include <colliders/SphereCollider.h>
#include <colliders/CapsuleCollider.h>

namespace mtrx
{
	BoxCollider::BoxCollider(const glm::vec3& center) : ConvexShapeCollider(ColliderType::Box, center), halfExtents(glm::vec3(0.5, 0.5, 0.5))
	{
		// Vertices of a box
		vertices =
		{
			new glm::vec3(-0.5, 0.5, 0.5),
			new glm::vec3(0.5, 0.5, 0.5),
			new glm::vec3(-0.5, -0.5, 0.5),
			new glm::vec3(0.5, -0.5, 0.5),
			new glm::vec3(-0.5, 0.5, -0.5),
			new glm::vec3(0.5, 0.5, -0.5),
			new glm::vec3(-0.5, -0.5, -0.5),
			new glm::vec3(0.5, -0.5, -0.5),
		};
	}

	BoxCollider::BoxCollider(const BoxCollider& collider1, const BoxCollider collider2)
	{
		// Create a bounding box from the 2 other bounding boxes
	}

	BoxCollider::~BoxCollider() 
	{}

	// Gives us whether there is a collision occurring
	bool BoxCollider::CheckCollision(const Collider& col)
	{
		bool collision;
		switch (col.GetColliderType())
		{
			case ColliderType::Sphere:
			{
				std::cout << "Box Sphere collision detection" << std::endl;
				const mtrx::SphereCollider& collider = static_cast<const mtrx::SphereCollider&>(col);
				collision = CollisionUtil::SphereBoxCollision(collider.GetPosition(), transform.position, collider.radius, axes, halfExtents);
				break;
			}
			case ColliderType::Box:
			{
				std::cout << "Box Box collision detection" << std::endl;
				const mtrx::BoxCollider& collider = static_cast<const mtrx::BoxCollider&>(col);
				collision = CollisionUtil::BoxBoxCollision(*this, collider);
				break;
			}
			case ColliderType::Capsule:
			{
				std::cout << "Box Capsule collision detection" << std::endl;
				const mtrx::CapsuleCollider& collider = static_cast<const mtrx::CapsuleCollider&>(col);
				collision = CollisionUtil::BoxCapsuleCollision(transform.position, collider.GetPosition(), collider.A, collider.B, collider.radii, axes, halfExtents);
				break;
			}
			case ColliderType::Mesh:
			{
				std::cout << "Box Mesh collision detection not implemented yet" << std::endl;
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

	// Raycast with box colliders
	bool BoxCollider::RaycastCollision(const Ray& ray)
	{
		return CollisionUtil::RayBoxCollision(ray.startPosition, ray.direction, transform.position, axes, halfExtents);
	}

	float BoxCollider::GetSize()
	{
		return 0.f;
	}

	float BoxCollider::GetGrowth(const BoxCollider& boxCollider)
	{
		return 0.f;
	}
}