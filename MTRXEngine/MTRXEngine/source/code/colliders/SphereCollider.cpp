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
	SphereCollider::SphereCollider(const glm::vec3& center, const glm::quat& orientation, const glm::vec3& scale, float radius) :
		Collider(ColliderType::Sphere, center, orientation, scale), radius(radius)
	{}

	SphereCollider::SphereCollider(const Transform& transform, float radius) : 
		Collider(ColliderType::Sphere, transform), radius(radius)
	{}

	SphereCollider::SphereCollider(const SphereCollider& collider1, const SphereCollider& collider2) : Collider(ColliderType::Sphere)
	{
		// Create a sphere encapsulating the 2 sphere colliders
		const glm::vec3& position1 = collider1.GetPosition();
		const glm::vec3& position2 = collider2.GetPosition();

		glm::vec3 difference = position2 - position1;
		float distanceSqr = glm::length2(difference);
		float diffRadius = collider1.radius - collider2.radius;

		if (diffRadius * diffRadius >= distanceSqr)
		{
			// One sphere is inside another one
			if (collider1.radius > collider2.radius)
			{
				SetPosition(position1);
				radius = collider1.radius;
			}
			else
			{
				SetPosition(position2);
				radius = collider2.radius;
			}
		}
		else
		{
			distanceSqr = sqrt(distanceSqr);
			radius = (distanceSqr + collider1.radius + collider2.radius) * 0.5f;

			SetPosition(position1);
			if (distanceSqr > 0)
				SetPosition(GetPosition() + (difference * (radius - collider1.radius) / distanceSqr));
		}

		SetScale(glm::vec3(radius * 2, 0.f, 0.f));
	}

	SphereCollider::~SphereCollider()
	{}

	bool SphereCollider::CheckCollision(const Collider& col)
	{
		// TBD: Collision detection architecture is ugly and needs to be redone
		bool isColliding; 
		switch (col.GetColliderType())
		{
			case ColliderType::Sphere:
			{
				//std::cout << "SPHERE SPHERE COLLISON DETECTION" << std::endl;
				const SphereCollider& collider = static_cast<const SphereCollider&>(col);
				isColliding = CollisionUtil::SphereSphereCollision(GetPosition(), collider.GetPosition(), radius, collider.radius);
				break;
			}
			case ColliderType::Box:
			{
				//std::cout << "SPHERE BOX COLLISION DETECTION" << std::endl;
				const BoxCollider& collider = static_cast<const BoxCollider&>(col);
				isColliding = CollisionUtil::SphereBoxCollision(GetPosition(), collider.GetPosition(), radius, collider.GetAxes(), collider.halfExtents);
				break;
			}
			case ColliderType::Capsule:
			{
				//std::cout << "SPHERE CAPSULE COLLISION DETECTION" << std::endl;
				const CapsuleCollider& collider = static_cast<const CapsuleCollider&>(col);
				isColliding = CollisionUtil::SphereCapsuleCollision(GetPosition(), collider.GetPosition(), radius, collider.radii, collider.A, collider.B);
				break;
			}
			case ColliderType::Mesh:
			{
				//std::cout << "SPHERE MESH COLLISION DETECTION" << std::endl;
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
		return CollisionUtil::RaySphereCollision(GetPosition(), radius, ray.startPosition, ray.direction);
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