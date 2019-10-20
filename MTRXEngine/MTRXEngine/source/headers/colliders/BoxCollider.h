#pragma once

#include <colliders/ConvexShapeCollider.h>
#include <utils/CollisionUtil.h>
#include <IBoundingVolume.h>
#include <math/Transform.h>

namespace mtrx
{
	// Forward declarations
	//class SphereCollider;
	//class CapsuleCollider;
	//class MeshCollider;

	class BoxCollider : public ConvexShapeCollider, public IBoundingVolume
	{
	public:
		glm::vec3 halfExtents;

		BoxCollider(const glm::vec3& center = glm::vec3(), const glm::quat& orientation = glm::angleAxis(0.f, worldUp), const glm::vec3& scale = glm::vec3(1, 1, 1));
		BoxCollider(const Transform& transform = Transform());
		BoxCollider(const BoxCollider& collider1, const BoxCollider& collider2); // Used for BVH construction
		virtual ~BoxCollider() = default;

		virtual bool CheckCollision(const mtrx::Collider& collider) override { Collider::CheckCollision(collider); };
		
		// Raycast with box colliders
		virtual inline bool RaycastCollision(const Ray& ray) override { return CollisionUtil::RayBoxCollision(ray.startPosition, ray.direction, GetPosition(), axes.axes, halfExtents); }
		// length * breadth * height
		virtual inline float GetSize() override { return halfExtents[0] * halfExtents[1] * halfExtents[2] * 8; }
		virtual inline float GetGrowth(const BoxCollider& boxCollider) { return 0.f; }

		inline const glm::vec3* GetAxes() const { return axes.axes; }
		inline const glm::vec3& GetHalfExtents() const { return halfExtents; }
		inline glm::vec3& GetHalfExtents() { return halfExtents; }

	private:
		ObjectAxes axes;
	};
}