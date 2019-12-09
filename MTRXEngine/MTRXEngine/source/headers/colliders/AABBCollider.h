#pragma once

#include <colliders/ConvexShapeCollider.h>
#include <colliders/IBoundingVolume.h>
#include <utils/RaycastCollisionUtil.h>

namespace mtrx
{
	/**
	 * @brief Implmentation of an Axis Aligned Bounding Box used for collision systems
	 * 
	 */
	class AABBCollider : public ConvexShapeCollider, IBoundingVolume
	{
	public:
		/**
		 * @brief Construct a new AABBCollider object
		 * 
		 * @param center Center point of the AABB
		 * @param scale Scale vector of the AABB @see mtrx::Transform
		 */
		AABBCollider(const glm::vec3& center = glm::vec3(), const glm::vec3& scale = glm::vec3(1, 1, 1));

		//AABBCollider(const AABBCollider& aabb, const AABBCollider& aabb1);
		
		/**
		 * @brief Destroy the AABBCollider object
		 * 
		 */
		virtual ~AABBCollider() = default;

		/**
		 * @brief Collision function between a ray and an AABB
		 * 
		 * @param ray The ray that we will be checking collision on @see mtrx::ray
		 * 
		 * @return true If there is a collision 
		 * @return false If there is no collision 
		 */
		virtual inline bool RaycastCollision(const Ray& ray) override
		{
			return RaycastCollisionUtil::RayAABBCollision(ray.startPosition, ray.direction, GetPosition(), axes.axes, halfExtents);
		}

		/**
		 * @brief This function should not be used and is empty as AABBs should not 
		 * change orientations
		 * 
		 * @param orientation 
		 */
		virtual inline void SetOrientation(const glm::quat& orientation) override {} // Must not change orientation

		/**
		 * @brief Calculate the size of an AABB 
		 * defined as length * width * height
		 * 
		 */
		virtual inline float GetSize() override { return halfExtents[0] * halfExtents[1] * halfExtents[2] * 8.f; }	

		// virtual inline float GetGrowth(const AABBCollider& aabb) 
		// {
		// 	AABBCollider aabb1 = AABBCollider(*this, aabb);
		// }

		/**
		 * @brief Get the Axes that define the AABB's world
		 * They would constant in this case since the orientation 
		 * never changes
		 * 
		 * @return const glm::vec3* pointer to the array of 3 axes
		 */
		inline const glm::vec3* GetAxes() const { return axes.axes; }

		/**
		 * @brief Get the Half Extents of the AABB (This is the const version)
		 * 
		 * @return const float* pointer to the array of half extents values in each dimension
		 */
		inline const float* GetHalfExtents() const { return halfExtents; }

		/**
		 * Non const version of GetHalfExtents()
		 * 
		 * @return float* pointer to the array of halfExtents 
		 */
		inline float* GetHalfExtents() { return halfExtents; }

		/**
		 * @brief Set the Scale object overriden to modify 
		 * the halfExtents to represent scale change
		 * 
		 * @param scale The new scale vector of the AABB
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
		ObjectAxes axes;
	};
}