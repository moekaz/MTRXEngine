#pragma once

#include <colliders/ConvexShapeCollider.h>
#include <math/Transform.h>

namespace mtrx
{
	class OOBBCollider : public ConvexShapeCollider
	{
	public:
		OOBBCollider(const glm::vec3& center = glm::vec3(), const glm::quat& orientation = glm::angleAxis(0.f, glm::vec3(0, 1, 0)), const glm::vec3& scale = glm::vec3(1, 1, 1));
		OOBBCollider(const Transform& transform = Transform());
		virtual ~OOBBCollider() = default;

		virtual inline bool RaycastCollision(const Ray& ray) override
		{
			return RaycastCollisionUtil::RayBoxCollision(ray.startPosition, ray.direction, GetPosition(), GetAxes(), halfExtents);
		}
		
		inline const glm::vec3* GetAxes() const
		{
			if (!transformModified)
				return axes.axes;

			axes[0] = GetSide();
			axes[1] = GetUp();
			axes[2] = GetForward();

			return axes.axes;
		}

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