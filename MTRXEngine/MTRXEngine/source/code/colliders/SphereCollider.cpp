/*
	Author: Mohamed Kazma
	Description: implementation of a sphere collider
*/

#include <PrecompiledHeader.h>
#include <colliders/SphereCollider.h>
#include <colliders/BoxCollider.h>
#include <colliders/CapsuleCollider.h>

namespace mtrx
{
	SphereCollider::SphereCollider(const glm::vec3& center, float radius) : Collider(ColliderType::Sphere, center), radius(radius) 
	{}

	SphereCollider::SphereCollider(const SphereCollider& collider1, const SphereCollider& collider2) : Collider(ColliderType::Sphere)
	{
		// Create a sphere encapsulating the 2 sphere colliders
		glm::vec3 difference = collider2.transform.position - collider1.transform.position;
		float distanceSqr = glm::length2(difference);
		float diffRadius = collider1.radius - collider2.radius;

		if (diffRadius * diffRadius >= distanceSqr)
		{
			// One sphere is inside another one
			if (collider1.radius > collider2.radius)
			{
				transform.position = collider1.transform.position;
				radius = collider1.radius;
			}
			else
			{
				transform.position = collider2.transform.position;
				radius = collider2.radius;
			}
		}
		else
		{
			// Can we optimize this call out
			distanceSqr = sqrt(distanceSqr);
			radius = (distanceSqr + collider1.radius + collider2.radius) * 0.5f;

			transform.position = collider1.transform.position;
			if (distanceSqr > 0)
				transform.position += difference * (radius - collider1.radius) / distanceSqr;
		}
	}

	SphereCollider::~SphereCollider()
	{}

	bool SphereCollider::CheckCollision(const Collider& col)
	{
		bool isColliding; 
		switch (col.GetColliderType())
		{
			case ColliderType::Sphere:
			{
				std::cout << "SPHERE SPHERE COLLISON DETECTION" << std::endl;
				const SphereCollider& collider = static_cast<const SphereCollider&>(col);
				isColliding = CollisionUtil::SphereSphereCollision(transform.position, collider.GetPosition(), radius, collider.radius);
				break;
			}
			case ColliderType::Box:
			{
				std::cout << "SPHERE BOX COLLISION DETECTION" << std::endl;
				const BoxCollider& collider = static_cast<const BoxCollider&>(col);
				isColliding = CollisionUtil::SphereBoxCollision(transform.position, collider.GetPosition(), radius, collider.GetAxes(), collider.halfExtents);
				break;
			}
			case ColliderType::Capsule:
			{
				std::cout << "SPHERE CAPSULE COLLISION DETECTION" << std::endl;
				const CapsuleCollider& collider = static_cast<const CapsuleCollider&>(col);
				isColliding = CollisionUtil::SphereCapsuleCollision(transform.position, collider.GetPosition(), radius, collider.radii, collider.A, collider.B);
				break;
			}
			case ColliderType::Mesh:
			{
				std::cout << "SPHERE MESH COLLISION DETECTION" << std::endl;
				break;
			}
			default:
			{
				std::cout << "SHIT HIT THE FAN" << std::endl;
				isColliding = false;
			}
		}

		return isColliding;
	}

	bool SphereCollider::RaycastCollision(const Ray& ray)
	{
		return CollisionUtil::RaySphereCollision(transform.position, radius, ray.startPosition, ray.direction);
	}

	float SphereCollider::GetSize()
	{
		return 1.333333f * PI * radius * radius * radius;
	}

	float SphereCollider::GetGrowth(const SphereCollider& sphereCollider)
	{
		SphereCollider collider = SphereCollider(*this, sphereCollider);
		return collider.radius * collider.radius - radius * radius;
	}
}