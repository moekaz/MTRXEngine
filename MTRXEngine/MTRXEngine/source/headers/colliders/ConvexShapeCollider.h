#pragma once

#include <colliders/Collider.h>
#include <utils/CollisionUtil.h>
#include <math/Transform.h>
#include <math/Ray.h>

namespace mtrx
{
	/**
	 * Implementation of a Convex Shape collider
	 * 
	 */
	class ConvexShapeCollider : public Collider
	{
	public:
		/**
		 * @brief Construct a new Convex Shape Collider object
		 * 
		 * @param colliderType The type of collider we are creating. The default is a convex shape however we can have other type @see mtrx::AABBCollider @see mtrx::OOBBCollider
		 * @param center The center of the collider
		 * @param orientation The orientation of the collider
		 * @param scale The scale of the collider
		 */
		ConvexShapeCollider(const ColliderType& colliderType = ColliderType::ConvexShape, const glm::vec3& center = glm::vec3(), const glm::quat& orientation = glm::angleAxis(0.f, worldUp), const glm::vec3& scale = glm::vec3(1, 1, 1));
		
		/**
		 * @brief Construct a new Convex Shape Collider object
		 * 
		 * @param colliderType The type of collider we are creating. The default is a convex shape however we can have other type @see mtrx::AABBCollider @see mtrx::OOBBCollider
		 * @param transform The transform of the collider @see mtrx::Transform
		 */
		ConvexShapeCollider(const ColliderType& colliderType = ColliderType::ConvexShape, const Transform& transform = Transform());

		/**
		 * @brief Construct a new Convex Shape Collider object
		 * 
		 * @param colliderType The type of collider we are creating. The default is a convex shape however we can have other type @see mtrx::AABBCollider @see mtrx::OOBBCollider
		 * @param vertices The vertices of the convex shape collider
		 * @param center The center of the collider
		 * @param orientation The orientation of the collider
		 * @param scale The scale of the collider
		 */
		ConvexShapeCollider(const ColliderType& colliderType = ColliderType::ConvexShape, const std::vector<glm::vec3*>& vertices = std::vector<glm::vec3*>(), const glm::vec3& center = glm::vec3(), const glm::quat& orientation = glm::angleAxis(0.f, glm::vec3(0, 1, 0)), const glm::vec3& scale = glm::vec3(1, 1, 1));
		
		/**
		 * @brief Construct a new Convex Shape Collider object
		 * 
		 * @param colliderType The type of collider we are creating. The default is a convex shape however we can have other type @see mtrx::AABBCollider @see mtrx::OOBBCollider
		 * @param vertices The vertices of the convex shape collider
		 * @param transform The transform of the collider @see mtrx::Trnasform
		 */
		ConvexShapeCollider(const ColliderType& colliderType = ColliderType::ConvexShape, const std::vector<glm::vec3*>& vertices = std::vector<glm::vec3*>(), const Transform& transform = Transform());

		/**
		 * @brief Destroy the Convex Shape Collider object
		 * 
		 */
		virtual ~ConvexShapeCollider();

		/**
		 * @brief Raycast collision check with convex shape colliders
		 * 
		 * @param ray The ray that we want to cast
		 * @return true The ray and the colliders collide
		 * @return false The ray and colliders do not collide
		 */
		virtual bool RaycastCollision(const Ray& ray) override;

		// Vertices and model matrices
		/**
		 * @brief Get the Vertices of the convex shape collider
		 * 
		 * @return std::vector<glm::vec3*>* A pointer to the transformed vertices of the collider 
		 */
		std::vector<glm::vec3*>* GetVertices() const;
		
		/**
		 * @brief Get the Model Matrix of the convex shape collider
		 * 
		 * @return glm::mat4 The model matrix of the convex shape collider
		 */
		glm::mat4 GetModelMatrix() const;

		/**
		 * @brief Set the Position of the convex shape collider
		 * 
		 * @param pos The new position of the collider
		 */
		virtual inline void SetPosition(const glm::vec3& pos) override { Collider::SetPosition(pos); transformModified = true; }
		
		/**
		 * @brief Set the Scale of the collider
		 * 
		 * @param scale The new scale of the collider
		 */
		virtual inline void SetScale(const glm::vec3& scale) override { Collider::SetScale(scale); transformModified = true; }
		
		/**
		 * @brief Set the Orientation of the collider
		 * 
		 * @param quat The new orientation of the collider
		 */
		virtual inline void SetOrientation(const glm::quat& quat) override { Collider::SetOrientation(quat); transformModified = true; }

	protected:
		std::vector<glm::vec3*> vertices;
		mutable std::vector<glm::vec3*> transformedVertices;
		mutable bool transformModified;
	};
}