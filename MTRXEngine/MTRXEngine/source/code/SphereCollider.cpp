/*
	Author: Mohamed Kazma
	Description: implementation of a sphere collider
*/

#include <PrecompiledHeader.h>
#include <SphereCollider.h>
#include <BoxCollider.h>
#include <CapsuleCollider.h>

namespace MTRX
{
	/* Constructor */
	SphereCollider::SphereCollider(const glm::vec3& center, float radius) : Collider(ColliderType::Sphere, center), radius(radius) {}

	/* Destructor */
	SphereCollider::~SphereCollider() {}

	/* Functions */

	// Update the values of the collider
	void SphereCollider::PhysicsUpdate() {}

	// Checking for collision since this is going to be polymorphic it would make sense to use a general collider and work from there
	bool SphereCollider::CheckCollision(const Collider& col)
	{
		switch (col.type)
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
				isColliding = CollisionUtil::SphereBoxCollision(center, collider.GetPosition(), radius, collider.min, collider.max, collider.GetAxes(), collider.halfExtents);
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

		UpdateCollisionInfo();	// Update info about when the collision started etc...
		return isColliding;
	}

	// Raycast with spheres
	bool SphereCollider::RaycastCollision(const Ray& ray)
	{
		return CollisionUtil::RaySphereCollision(center, radius, ray.startPosition, ray.direction);
	}

	// Print out values of the collider
	std::ostream& operator<<(std::ostream& os, const SphereCollider& sphCollider)
	{
		return os << "Sphere Collider:" << std::endl
			<< "---------------" << std::endl
			<< "Center: " << std::endl
			<< "x: " << sphCollider.center.x << std::endl
			<< "y: " << sphCollider.center.y << std::endl
			<< "z: " << sphCollider.center.z << std::endl
			<< "Radius: " << sphCollider.radius;
	}
}