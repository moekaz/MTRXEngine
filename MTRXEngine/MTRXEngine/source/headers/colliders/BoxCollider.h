#pragma once

#include <colliders/ConvexShapeCollider.h>
#include <utils/RaycastCollisionUtil.h>
#include <colliders/IBoundingVolume.h>
#include <math/Transform.h>

namespace mtrx
{
	// TBD: MAYBE ONE INSTANCE OF VERTICES IS JUST FINE AS IT DOESN'T CHANGE
	class BoxCollider : public ConvexShapeCollider, public IBoundingVolume
	{
	public:
		BoxCollider(const glm::vec3& center = glm::vec3(), const glm::quat& orientation = glm::angleAxis(0.f, worldUp), const glm::vec3& scale = glm::vec3(1, 1, 1));
		BoxCollider(const Transform& transform = Transform());
		BoxCollider(const BoxCollider& collider1, const BoxCollider& collider2); // Used for BVH construction
		virtual ~BoxCollider() = default;

		virtual bool CheckCollision(const mtrx::Collider& collider) override { return Collider::CheckCollision(collider); };
		
		// Raycast with box colliders
		virtual inline bool RaycastCollision(const Ray& ray) override { return RaycastCollisionUtil::RayBoxCollision(ray.startPosition, ray.direction, GetPosition(), axes.axes, halfExtents); }
		
		// length * breadth * height
		virtual inline float GetSize() override { return halfExtents[0] * halfExtents[1] * halfExtents[2] * 8.f; }
		virtual inline float GetGrowth(const BoxCollider& boxCollider) { return 0.f; }

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
		ObjectAxes axes;
		float halfExtents[3];
	};
}