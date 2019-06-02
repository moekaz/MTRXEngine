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
		glm::vec3 difference = collider2.center - collider1.center;
		float distanceSqr = glm::length2(difference);
		float diffRadius = collider1.radius - collider2.radius;

		if (diffRadius * diffRadius >= distanceSqr)
		{
			// One sphere is inside another one
			if (collider1.radius > collider2.radius)
			{
				center = collider1.center;
				radius = collider1.radius;
			}
			else
			{
				center = collider2.center;
				radius = collider2.radius;
			}
		}
		else
		{
			// Can we optimize this call out
			distanceSqr = sqrt(distanceSqr);
			radius = (distanceSqr + collider1.radius + collider2.radius) * 0.5f;

			center = collider1.center;
			if (distanceSqr > 0)
				center += difference * (radius - collider1.radius) / distanceSqr;
		}
	}

	SphereCollider::~SphereCollider()
	{}

	// Checking for collision since this is going to be polymorphic it would make sense to use a general collider and work from there
	bool SphereCollider::CheckCollision(const Collider& col)
	{
		bool isColliding; 
		switch (col.GetColliderType())
		{
			case ColliderType::Sphere:
			{
				std::cout << "SPHERE SPHERE COLLISON DETECTION" << std::endl;
				const SphereCollider& collider = static_cast<const SphereCollider&>(col);
				isColliding = CollisionUtil::SphereSphereCollision(center, collider.GetPosition(), radius, collider.radius);
				break;
			}
			case ColliderType::Box:
			{
				std::cout << "SPHERE BOX COLLISION DETECTION" << std::endl;
				const BoxCollider& collider = static_cast<const BoxCollider&>(col);
				isColliding = CollisionUtil::SphereBoxCollision(center, collider.GetPosition(), radius, collider.GetAxes(), collider.halfExtents);
				break;
			}
			case ColliderType::Capsule:
			{
				std::cout << "SPHERE CAPSULE COLLISION DETECTION" << std::endl;
				const CapsuleCollider& collider = static_cast<const CapsuleCollider&>(col);
				isColliding = CollisionUtil::SphereCapsuleCollision(center, collider.GetPosition(), radius, collider.radii, collider.A, collider.B);
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

	// Raycast with spheres
	bool SphereCollider::RaycastCollision(const Ray& ray)
	{
		return CollisionUtil::RaySphereCollision(center, radius, ray.startPosition, ray.direction);
	}

	float SphereCollider::GetSize()
	{
		return 1.333333f * pi * radius * radius * radius;
	}

	float SphereCollider::GetGrowth(const SphereCollider& sphereCollider)
	{
		SphereCollider collider = SphereCollider(*this, sphereCollider);
		return collider.radius * collider.radius - radius * radius;
	}
}