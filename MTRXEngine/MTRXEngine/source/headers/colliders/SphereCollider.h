#pragma once

#include <colliders/Collider.h>
#include <utils/RaycastUtil.h>
#include <colliders/IBoundingVolume.h>
#include <math/Transform.h>

namespace mtrx
{
	// Forward declarations
	//class BoxCollider;
	//class CapsulesCollider;
	//class MeshCollider;

	class SphereCollider : public Collider, public IBoundingVolume
	{
	public:
		float radius;

		SphereCollider(const glm::vec3& center = glm::vec3(), const glm::quat& orientation = glm::angleAxis(0.f, worldUp), const glm::vec3& scale = glm::vec3(1, 1, 1), float radius = 0.5);
		SphereCollider(const Transform& transform = Transform(), float radius = 0.5);
		SphereCollider(const SphereCollider& collider1, const SphereCollider& collider2); // Used for BVH construction
		virtual ~SphereCollider() = default;

		virtual inline bool RaycastCollision(const Ray& ray) override { return RaycastUtil::RaySphereCollision(GetPosition(), radius, ray.startPosition, ray.direction); }
		virtual inline float GetSize() override { return 1.333333f * PI * radius * radius * radius; }
		virtual inline float GetGrowth(const SphereCollider& sphereCollider) { return SQR(SphereCollider(*this, sphereCollider).radius) - SQR(radius); }

		virtual inline void SetScale(const glm::vec3& scale) override
		{
			// NOTE: ONLY THE X VALUE OF THE SCALE IS USED FOR UPDATING THE SPHERE COLLIDER
			Collider::SetScale(scale);
			radius = 0.5f * scale.x;
		}
	};
}