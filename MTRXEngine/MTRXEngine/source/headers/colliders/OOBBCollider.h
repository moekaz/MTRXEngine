#pragma once

#include <colliders/ConvexShapeCollider.h>
#include <math/Transform.h>

namespace mtrx
{
	/**
	 * Implementation of OOBBs 
	 * 
	 */
	class OOBBCollider : public ConvexShapeCollider
	{
	public:

		/**
		 * @brief Construct a new OOBBCollider object
		 * 
		 * @param center Center of the collider
		 * @param orientation Orientation of the collider
		 * @param scale The scale of the collider
		 */
		OOBBCollider(const glm::vec3& center = glm::vec3(), const glm::quat& orientation = glm::angleAxis(0.f, glm::vec3(0, 1, 0)), const glm::vec3& scale = glm::vec3(1, 1, 1));

		/**
		 * @brief Construct a new OOBBCollider object
		 * 
		 * @param transform The transform of the collider @mtrx::Transform
		 */
		OOBBCollider(const Transform& transform = Transform());

		/**
		 * @brief Destroy the OOBBCollider object
		 * 
		 */
		virtual ~OOBBCollider() = default;

		/**
		 * @brief Raycast OOBB collision detection algorithm
		 * 
		 * @param ray Ray that we want to check collision for @see mtrx::Ray
		 * @return true The ray and collider collide
		 * @return false The ray and collider do not collide
		 */
		virtual inline bool RaycastCollision(const Ray& ray) override
		{
			return RaycastCollisionUtil::RayBoxCollision(ray.startPosition, ray.direction, GetPosition(), GetAxes(), halfExtents);
		}
		
		/**
		 * @brief Get the Axes of the collider
		 * 
		 * @return const glm::vec3* Array of the axes of the OOBB
		 */
		inline const glm::vec3* GetAxes() const
		{
			if (!transformModified)
				return axes.axes;

			axes[0] = GetForward();
			axes[1] = GetUp();
			axes[2] = GetSide();

			return axes.axes;
		}

		/**
		 * @brief Get the Half Extents of the OOBB collider
		 * 
		 * @return const float* The half extents of the collider
		 */
		inline const float* GetHalfExtents() const { return halfExtents; }
		
		/**
		 * @brief Get the Half Extents of the OOBB collider
		 * 
		 * @return float* The half extents of the collider
		 */
		inline float* GetHalfExtents() { return halfExtents; }

		/**
		 * @brief Set the Scale of the collider
		 * 
		 * @param scale The scale of the collider
		 */
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
		mutable ObjectAxes axes;
	};
}