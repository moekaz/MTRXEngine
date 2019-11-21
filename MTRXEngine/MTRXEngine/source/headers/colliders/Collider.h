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
		Collider(const ColliderType& colliderType, const glm::vec3& center = glm::vec3(), const glm::quat& orientation = glm::angleAxis(0.f, glm::vec3(0, 1, 0)), const glm::vec3& scale = glm::vec3(1, 1, 1), bool isConvex = false);
		Collider(const ColliderType& colliderType, const Transform& transform, bool isConvex = false);
		virtual ~Collider() = default;
		
		inline bool CheckCollision(const Collider& collider) { return ColliderDetectionUtil::Collide(*this, collider); }
		virtual bool RaycastCollision(const Ray& ray) = 0;

		// Getters
		inline const glm::vec3& GetPosition() const { return transform.GetPosition(); }
		inline const glm::vec3& GetScale() const { return transform.GetScale(); }
		inline const glm::quat& GetOrientation() const { return transform.GetOrientation(); }
		inline const ColliderType& GetColliderType() const { return type; }
		inline const int GetColliderId() const { return colliderId; }
		inline const bool IsConvex() const { return isConvexShape; }
		inline const glm::vec3 GetForward() const { return glm::fastNormalize(transform.GetOrientation() * worldForward); }
		inline const glm::vec3 GetSide() const { return glm::fastNormalize(transform.GetOrientation() * worldSide); }
		inline const glm::vec3 GetUp() const { return glm::fastNormalize(transform.GetOrientation() * worldUp); }

		// Setters
		virtual inline void SetPosition(const glm::vec3& center) { transform.SetPosition(center); }
		virtual inline void SetScale(const glm::vec3& scale) { transform.SetScale(scale); }
		virtual inline void SetOrientation(const glm::quat& orientation) { transform.SetOrientation(orientation); }
	
	private:
		static int id;

	protected:
		int colliderId; // The id of collider
		ColliderType type; // The collider type
		bool isConvexShape; // Whether it is a convex shape collider or not
		mutable ObjectAxes axes; // The axes that define this collider's world
		Transform transform; // position orientation and scale of the collider
	};
}