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
	BoxCollider::BoxCollider(const glm::vec3& center, const glm::quat& orientation, const glm::vec3& scale) : 
		BoxCollider(Transform(center, orientation, scale))
	{}

	BoxCollider::BoxCollider(const Transform& transform) :
		ConvexShapeCollider(ColliderType::Box, transform), 
		halfExtents(glm::vec3(0.5f * transform.GetScale().x, 0.5f * transform.GetScale().y, 0.5f * transform.GetScale().z))
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


		transformedVertices.resize(vertices.size());
		for (int i = 0; i < vertices.size(); ++i)
		{
			transformedVertices[i] = new glm::vec3();
		}
	}

	BoxCollider::BoxCollider(const BoxCollider& collider1, const BoxCollider& collider2) : ConvexShapeCollider(ColliderType::Box, Transform())
	{
		// TBD: Constructor for box collider of box colliders needs to be implemented
		// Create a bounding box from the 2 other bounding boxes
	}

	BoxCollider::~BoxCollider()
	{}

	bool BoxCollider::CheckCollision(const Collider& col)
	{
		// TBD: Collision detection architecture is ugly and needs to be redone
		bool collision;
		switch (col.GetColliderType())
		{
			case ColliderType::Sphere:
			{
				//std::cout << "Box Sphere collision detection" << std::endl;
				const SphereCollider& collider = static_cast<const SphereCollider&>(col);
				collision = CollisionUtil::SphereBoxCollision(collider.GetPosition(), GetPosition(), collider.radius, axes.axes, halfExtents);
				break;
			}
			case ColliderType::Box:
			{
				//std::cout << "Box Box collision detection" << std::endl;
				const BoxCollider& collider = static_cast<const BoxCollider&>(col);
				collision = CollisionUtil::BoxBoxCollision(*this, collider);
				break;
			}
			case ColliderType::Capsule:
			{
				//std::cout << "Box Capsule collision detection" << std::endl;
				const mtrx::CapsuleCollider& collider = static_cast<const mtrx::CapsuleCollider&>(col);
				collision = CollisionUtil::BoxCapsuleCollision(GetPosition(), collider.GetPosition(), collider.A, collider.B, collider.radii, axes.axes, halfExtents);
				break;
			}
			case ColliderType::Mesh:
			{
				//std::cout << "Box Mesh collision detection not implemented yet" << std::endl;
				break;
			}
			default:
			{
				//std::cout << "HOUSTON WE HAVE A PROBLEM" << std::endl;
				collision = false;
			}
		}

		return collision;
	}

	// Raycast with box colliders
	bool BoxCollider::RaycastCollision(const Ray& ray)
	{
		return CollisionUtil::RayBoxCollision(ray.startPosition, ray.direction, GetPosition(), axes.axes, halfExtents);
	}

	float BoxCollider::GetSize()
	{
		// length * breadth * height
		return halfExtents[0] * halfExtents[1] * halfExtents[2] * 8;
	}

	float BoxCollider::GetGrowth(const BoxCollider& boxCollider)
	{
		return 0.f;
	}
}