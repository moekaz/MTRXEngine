#pragma once

#include <utils/PhysicsUtil.h>
#include <colliders/Collider.h>
#include <math/Ray.h>

namespace mtrx
{
	/**
	 * @brief Utility namespace used for raycasting functionality
	 * 
	 */
	namespace RaycastCollisionUtil
	{
		/**
		 * @brief Raycasting onto a sphere collider @see mtrx::SphereCollider @see mtrx::Ray
 		 * 
		 * @param sphereCenter Center of the sphere collider
		 * @param sphereRadius Radius of the sphere collider
		 * @param startPointRay Start point of the ray 
		 * @param rayDirection Normalized direction of the ray
		 * @return true The ray and the sphere collider collide
		 * @return false The ray and the sphere collider do not collide
		 */
		bool RaySphereCollision(const glm::vec3& sphereCenter, float sphereRadius, const glm::vec3& startPointRay, const glm::vec3& rayDirection);

		/**
		 * @brief Raycasting onto a capsule collider @see mtrx::CapsuleCollider @see mtrx::Ray
		 * 
		 * @param startPositionRay The starting position of the ray
		 * @param direction The normalized direction of the ray
		 * @param A The center of the topmost sphere of the capsule
		 * @param B The center of the bottommost sphere of the capsule
		 * @param capsRadius The radius of the capsule
		 * @return true The ray and the capsule collider collide
		 * @return false The ray and the capsule collider do not collide
		 */
		bool RayCapsuleCollision(const glm::vec3& startPositionRay, const glm::vec3& direction, const glm::vec3& A, const glm::vec3& B, float capsRadius);
		
		/**
		 * @brief Raycasting onto a box collider @see mtrx::OOBBCollider @see mtrx::AABBCollider @see mtrx::Ray
		 * 
		 * @param rayStart The starting point of the ray
		 * @param rayDirection The normalized direction of the ray
		 * @param center The center of the box collider
		 * @param axes The axes of the collider
		 * @param halfExtents the half extents of the collider
		 * @return true The ray and box collide
		 * @return false The ray and box do not collide
		 */
		bool RayBoxCollision(const glm::vec3& rayStart, const glm::vec3& rayDirection, const glm::vec3& center, const glm::vec3* axes, const float* halfExtents);

		/**
		 * @brief NOT TESTED OR USED
		 * 
		 * @param colliders 
		 * @param filterColliders 
		 * @param rayStartPosition 
		 * @param rayDirection 
		 * @return Collider* 
		 */
		Collider* RaycastFiltered(const std::map<int, Collider*>& colliders, const std::vector<Collider*>& filterColliders, const glm::vec3& rayStartPosition, const glm::vec3& rayDirection);	// Raycast check on colliders filtered
		
		/**
		 * @brief NOT TESTED OR USED
		 * 
		 * @param colliders 
		 * @param rayStartPosition 
		 * @param rayDirection 
		 * @return Collider* 
		 */
		Collider* RaycastUnfiltered(const std::map<int, Collider*>& colliders, const glm::vec3& rayStartPosition, const glm::vec3& rayDirection);	// Raycast check for all colliders
	}
}