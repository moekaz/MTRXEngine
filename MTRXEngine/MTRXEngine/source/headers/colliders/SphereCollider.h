#pragma once

#include <colliders/Collider.h>
#include <utils/RaycastCollisionUtil.h>
#include <colliders/IBoundingVolume.h>
#include <math/Transform.h>

namespace mtrx
{
	/**
	 * Implmentation of a Sphere collider used in collision systems
	 * 
	 */
	class SphereCollider : public Collider, public IBoundingVolume
	{
	public:
		/**
		 * @brief Construct a new Sphere Collider object
		 * 
		 * @param center Center position of the sphere 
		 * @param orientation The orientation of the sphere
		 * @param scale The scale of the sphere (influences the radius of the collider)
		 * @param radius The default radius of the sphere
		 */
		SphereCollider(const glm::vec3& center = glm::vec3(), const glm::quat& orientation = glm::angleAxis(0.f, worldUp), const glm::vec3& scale = glm::vec3(1, 1, 1), float radius = 0.5);
		
		/**
		 * @brief Construct a new Sphere Collider object
		 * 
		 * @param transform The transform of the sphere (position, orientation, scale) @see mtrx::Transform
		 * @param radius the default radius of the sphere
		 */
		SphereCollider(const Transform& transform = Transform(), float radius = 0.5);
		
		/**
		 * @brief Construct a new Sphere Collider object that encompass 2 sphere
		 * colliders (used within the context of BVH construction mainly)
		 * 
		 * @param collider1 First sphere collider
		 * @param collider2 Second sphere collider
		 */
		SphereCollider(const SphereCollider& collider1, const SphereCollider& collider2); // Used for BVH construction
		
		/**
		 * @brief Destroy the Sphere Collider object
		 * 
		 */
		virtual ~SphereCollider() = default;

		/**
		 * @brief Raycast collision check for sphere colliders
		 * 
		 * @param ray The ray that we are check for collision on @see mtrx::Ray
		 * @return true The ray and the sphere collide
		 * @return false The ray and the sphere do not collide
		 */
		virtual inline bool RaycastCollision(const Ray& ray) override { return RaycastCollisionUtil::RaySphereCollision(GetPosition(), radius, ray.startPosition, ray.direction); }
		
		/**
		 * @brief Get the Size of the sphere (4/3 * PI * radius^3)
		 * 
		 * @return float 
		 */
		virtual inline float GetSize() override { return 1.333333f * PI * radius * radius * radius; }

		/**
		 * @brief Get the Growth when creating a sphere collider between 
		 * this collider and another sphere collider (for BVH construction)
		 * 
		 * @param sphereCollider the sphere collider that we want to add
		 * @return float The growth value of the resulting sphere collider
		 */
		virtual inline float GetGrowth(const SphereCollider& sphereCollider) { return SQR(SphereCollider(*this, sphereCollider).radius) - SQR(radius); }

		/**
		 * @brief Get the Radius of the collider
		 * 
		 * @return float Radius of collider 
		 */
		inline float GetRadius() const { return radius; }

		/**
		 * @brief Set the Radius of the collider
		 * 
		 * @param radius The value we want to set the radius to
		 */
		inline void SetRadius(float radius)
		{
			this->radius = radius;
			transform.GetScale().x = radius * 2.f;
		}

		/**
		 * @brief Set the Scale of the sphere collider.
		 * Only the X coordinate of the scale affects the collider, other coordinates are ignored
		 * 
		 * @param scale The value of the scale that we want to set the collider to
		 */
		virtual inline void SetScale(const glm::vec3& scale) override
		{
			Collider::SetScale(scale);
			radius = 0.5f * scale.x;
		}

	private:
		float radius;
	};
}