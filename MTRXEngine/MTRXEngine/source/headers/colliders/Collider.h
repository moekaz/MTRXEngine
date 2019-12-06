#pragma once

#include <Defs.h>
#include <math/Ray.h>
#include <math/Transform.h>
#include <utils/ColliderDetectionUtil.h>

namespace mtrx
{
	class Collider
	{
	public:	
		/**
		 * @brief Construct a new Collider object
		 * 
		 * @param colliderType The type of the collider 
		 * @param center Center of the collider
		 * @param orientation Orientation of the collider
		 * @param scale The scale of the collider
		 * @param isConvex Whether collider is a convex shape collider
		 */
		Collider(const ColliderType& colliderType, const glm::vec3& center = glm::vec3(), const glm::quat& orientation = glm::angleAxis(0.f, worldUp), const glm::vec3& scale = glm::vec3(1.f, 1.f, 1.f), bool isConvex = false);
		
		/**
		 * @brief Construct a new Collider object
		 * 
		 * @param colliderType The type of the collider
		 * @param transform The transform of the collider @see mtrx::Transform
		 * @param isConvex Whether the collider is a convex shape collider
		 */
		Collider(const ColliderType& colliderType, const Transform& transform, bool isConvex = false);
		
		/**
		 * @brief Destroy the Collider object
		 * 
		 */
		virtual ~Collider() = default;
		
		/**
		 * @brief Raycasting function that all colliders should have
		 * 
		 * @param ray Ray that we want to cast @see mtrx::Ray
		 * @return true The ray and the collider collide
		 * @return false The ray and the collider do not collide
		 */
		virtual bool RaycastCollision(const Ray& ray) = 0;

		/**
		 * @brief Check for collision with another collider
		 * 
		 * @param collider The collider that we want to check for collision
		 * @return true The collider is colliding with this collider 
		 * @return false The collider is not colliding with this collider
		 */
		inline bool CheckCollision(const Collider& collider) { return ColliderDetectionUtil::Collide(*this, collider); }

		// Getters
		/**
		 * @brief Get the Position of the collider
		 * 
		 * @return const glm::vec3& current position of the collider
		 */
		inline const glm::vec3& GetPosition() const { return transform.GetPosition(); }
		
		/**
		 * @brief Get the Scale of the collider
		 * 
		 * @return const glm::vec3& The current scale of the collider
		 */
		inline const glm::vec3& GetScale() const { return transform.GetScale(); }
		
		/**
		 * @brief Get the Orientation of the collider
		 * 
		 * @return const glm::quat& The current orientation of the collider
		 */
		inline const glm::quat& GetOrientation() const { return transform.GetOrientation(); }
		
		/**
		 * @brief Get the Collider Type of collider
		 * 
		 * @return const ColliderType& Enum collider type value
		 */
		inline const ColliderType& GetColliderType() const { return type; }
		
		/**
		 * @brief Get the Collider Id of the collider
		 * 
		 * @return const int Value of the Id of the collider
		 */
		inline const int GetColliderId() const { return colliderId; }
		
		/**
		 * @brief Is this collider convex
		 * 
		 * @return true The collider is a convex shape
		 * @return false The collider is not a convex shape
		 */
		inline const bool IsConvex() const { return isConvexShape; }
		
		/**
		 * @brief Get the Forward axis vector
		 * 
		 * @return const glm::vec3 The forward vector of this collider
		 */
		inline const glm::vec3 GetForward() const { return glm::fastNormalize(transform.GetOrientation() * worldForward); }
		
		/**
		 * @brief Get the Side axis vector
		 * 
		 * @return const glm::vec3 The side axis vector of the collider
		 */
		inline const glm::vec3 GetSide() const { return glm::fastNormalize(transform.GetOrientation() * worldSide); }
		
		/**
		 * @brief Get the Up axis vector
		 * 
		 * @return const glm::vec3 the up axis vector of the collider
		 */
		inline const glm::vec3 GetUp() const { return glm::fastNormalize(transform.GetOrientation() * worldUp); }

		// Setters
		/**
		 * @brief Set the Position of the collider
		 * 
		 * @param center The center position of this collider
		 */
		virtual inline void SetPosition(const glm::vec3& center) { transform.SetPosition(center); }
		
		/**
		 * @brief Set the Scale of the collider
		 * 
		 * @param scale The new scale of the collider
		 */
		virtual inline void SetScale(const glm::vec3& scale) { transform.SetScale(scale); }
		
		/**
		 * @brief Set the Orientation of the collider
		 * 
		 * @param orientation The new orientation of the collider
		 */
		virtual inline void SetOrientation(const glm::quat& orientation) { transform.SetOrientation(orientation); }
	
	private:
		static int id;

	protected:
		int colliderId;
		ColliderType type;
		bool isConvexShape;
		Transform transform;
	};
}