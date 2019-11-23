#pragma once

#include <colliders/ConvexShapeCollider.h>
#include <colliders/IBoundingVolume.h>

namespace mtrx
{
	class AABBCollider : public ConvexShapeCollider, IBoundingVolume
	{
	public:
		AABBCollider(const glm::vec3& center = glm::vec3(), const glm::vec3& scale = glm::vec3(1, 1, 1));
		AABBCollider(const AABBCollider& aabb, const AABBCollider& aabb1);
		virtual ~AABBCollider() = default;

		virtual inline bool RaycastCollision(const Ray& ray) override
		{
			return RaycastCollisionUtil::RayBoxCollision(ray.startPosition, ray.direction, GetPosition(), axes.axes, halfExtents);
		}

		virtual inline void SetOrientation(const glm::quat& orientation) override {} // Must not change orientation

		// length * breadth * height
		virtual inline float GetSize() override { return halfExtents[0] * halfExtents[1] * halfExtents[2] * 8.f; }
		
		// TBD: Implement Growth of AABB
		virtual inline float GetGrowth(const AABBCollider& boxCollider) { return 0.f; }

		inline const glm::vec3* GetAxes() const { return axes.axes; }
		inline const float* GetHalfExtents() const { return halfExtents; }
		inline float* GetHalfExtents() { return halfExtents; }

		virtual inline void SetScale(const glm::vec3& scale) override
		{
			Collider::SetScale(scale);
			glm::vec3& s = transform.GetScale();
			halfExtents[0] = 0.5f * s[0];
			halfExtents[1] = 0.5f * s[1];
			halfExtents[2] = 0.5f * s[2];
		}

	private:
		float halfExtents[3];
	};
}