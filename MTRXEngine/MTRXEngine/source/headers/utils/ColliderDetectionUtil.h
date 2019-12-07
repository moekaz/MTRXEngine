#pragma once

namespace mtrx
{
	// Forward Declarations
	class Collider;
	class SphereCollider;
	class CapsuleCollider;
	class AABBCollider;
	class OOBBCollider;
	class ConvexShapeCollider;

	/**
	 * @brief Utility namespace used for resolving collision detection algorithms to be used based on collider types @see mtrx::ColliderType
	 * 
	 */
	namespace ColliderDetectionUtil
	{
		/**
		 * @brief Check for whether 2 colliders collide
		 * 
		 * @param collider1 The first collider
		 * @param collider2 The second collider
		 * @return true The 2 colliders collide
		 * @return false the 2 colliders do not collide
		 */
		bool Collide(const Collider& collider1, const Collider& collider2);

		/**
		 * @brief Collision algorithm options for sphere colliders @see mtrx::SphereCollider
		 * 
		 * @param sphCollider The sphere collider
		 * @param collider The other collider
		 * @return true The 2 colliders collide
		 * @return false The 2 colliders do not collide
		 */
		bool SphereCollisionOptions(const SphereCollider& sphCollider, const Collider& collider);
		
		/**
		 * @brief Collision algorithm options for AABB colliders @see mtrx::AABBCollider
		 * 
		 * @param aabb The aabb collider
		 * @param collider The other collider
		 * @return true The 2 colliders collide
		 * @return false The 2 colliders do not collide
		 */
		bool AABBCollisionOptions(const AABBCollider& aabb, const Collider& collider);

		/**
		 * @brief Collision algorithm options for OOBB colliders @see mtrx::OOBBCollider
		 * 
		 * @param oobb The OOBB collider
		 * @param collider The other collider
		 * @return true The 2 colliders collide
		 * @return false The 2 colliders do not collide
		 */
		bool OOBBCollisionOptions(const OOBBCollider& oobb, const Collider& collider);
		
		/**
		 * @brief Collision algorithm options for capsule colliders @mtrx::CapsuleCollider
		 * 
		 * @param capCollider The capsule collider
		 * @param collider The other collider
		 * @return true The 2 colliders collide
		 * @return false The 2 colliders do not collide
		 */
		bool CapsuleCollisionOptions(const CapsuleCollider& capCollider, const Collider& collider);
		
		/**
		 * @brief Collision algotithm options for convex shape colliders @see mtrx::ConvexShapeCollider
		 * 
		 * @param convexCollider The convex shape collider
		 * @param collider The other collider
		 * @return true The 2 colliders collide
		 * @return false The 2 colliders do not collide
		 */
		bool ConvexShapeCollisionOptions(const ConvexShapeCollider& convexCollider, const Collider& collider);
	}
}