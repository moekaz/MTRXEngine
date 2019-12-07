#pragma once

#include <Defs.h>
#include <colliders/Collider.h>
#include <utils/RaycastCollisionUtil.h>
#include <colliders/IBoundingVolume.h>

namespace mtrx
{
	/**
	 * @brief Implementation of Capsule colliders
	 * 
	 */
	class CapsuleCollider : public Collider
	{
	public:
		glm::vec3 A;
		glm::vec3 B;

		/**
		 * @brief Construct a new Capsule Collider object
		 * 
		 * @param center Center of the capsule collider
		 * @param orientation Orientation of the capsule collider
		 * @param scale Scale of the capsule collider
		 * @param radii Radii of the spheres of the capsule collider
		 * @param height Height of the capsule collider
		 */
		CapsuleCollider(const glm::vec3& center = glm::vec3(), const glm::quat& orientation = glm::angleAxis(0.f, worldUp), const glm::vec3& scale = glm::vec3(1, 1, 1), float radii = 0.5f, float height = 1.f);
		
		/**
		 * @brief Construct a new Capsule Collider object
		 * 
		 * @param transform The transform that the capsule collider will use @see mtrx::Transform 
		 * @param radii Radii of the spheres of the capsule collider
		 * @param height Height of the capsule collider
		 */
		CapsuleCollider(const Transform& transform = Transform(), float radii = 0.5f, float height = 1.f);
		
		/**
		 * @brief Destroy the Capsule Collider object
		 * 
		 */
		virtual ~CapsuleCollider() = default;

		/**
		 * @brief Raycast ray and capsule collider collision detection algorithm
		 * 
		 * @param ray Ray used for raycast check @see mtrx::Ray
		 * @return true The ray and capsule collider collide
		 * @return false the ray and the capsule collider do not collide
		 */
		virtual bool RaycastCollision(const Ray& ray) override { return RaycastCollisionUtil::RayCapsuleCollision(ray.startPosition, ray.direction, A, B, radii); }

		/**
		 * @brief Get the Radii of the capsule colldier
		 * 
		 * @return float The radii of the capsule collider
		 */
		inline float GetRadii() const { return radii; }
		
		/**
		 * @brief Get the Height of the capsule collider
		 * 
		 * @return float The height of the capsule collider
		 */
		inline float GetHeight() const { return height; }		

		/**
		 * @brief Set the Radii of the capsule collider
		 * 
		 * @param radius The new value of radius
		 */
		inline void SetRadii(float radius) 
		{
			radii = radius;
			transform.GetScale().x = radius * 2.f;
		}

		/**
		 * @brief Set the Height of the capsule collider
		 * 
		 * @param height The new value of the height
		 */
		inline void SetHeight(float height)
		{
			this->height = height;
			transform.GetScale().y = height;
		}

		/**
		 * @brief Set the Scale of the capsule collider
		 * Only the X and Y values of the scale are the only applicable values on the collider
		 * The Z value is ignored
		 * 
		 * @param scale The new scale of the collider
		 */
		virtual inline void SetScale(const glm::vec3& scale) override
		{
			Collider::SetScale(scale);
			height = scale.y;
			radii = 0.5f * scale.x;
			A = GetPosition() - GetUp() * (height / 2);
			B = GetPosition() + GetUp() * (height / 2);
		}
		
		/**
		 * @brief Set the Position of the capsile collider
		 * 
		 * @param position The new position of the capsule collider
		 */
		virtual inline void SetPosition(const glm::vec3& position) override
		{
			glm::vec3 difference = position - GetPosition();
			Collider::SetPosition(position);
			A += difference;
			B += difference;
		}

		/**
		 * @brief Set the Orientation of the capsule collider
		 * 
		 * @param orientation The new orientation of the capsule collider
		 */
		virtual inline void SetOrientation(const glm::quat& orientation) override
		{
			Collider::SetOrientation(orientation);
			A = GetPosition() - GetUp() * (height / 2);
			B = GetPosition() + GetUp() * (height / 2);
		}

	private:
		float radii;
		float height;
	};
}