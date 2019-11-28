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
		Collider(const ColliderType& colliderType, const glm::vec3& center = glm::vec3(), const glm::quat& orientation = glm::angleAxis(0.f, worldUp), const glm::vec3& scale = glm::vec3(1.f, 1.f, 1.f), bool isConvex = false);
		Collider(const ColliderType& colliderType, const Transform& transform, bool isConvex = false);
		virtual ~Collider() = default;
		
		virtual bool RaycastCollision(const Ray& ray) = 0;

		inline bool CheckCollision(const Collider& collider) { return ColliderDetectionUtil::Collide(*this, collider); }

		// Getters
		inline const glm::vec3& GetPosition() const { return transform.GetPosition(); }
		inline const glm::vec3& GetScale() const { return transform.GetScale(); }
		inline const glm::quat& GetOrientation() const { return transform.GetOrientation(); }
		inline const ColliderType& GetColliderType() const { return type; }
		inline const int GetColliderId() const { return colliderId; }
		inline const bool IsConvex() const { return isConvexShape; }
		
		inline const glm::vec3 GetForward() const 
		{
			axes[0] = glm::fastNormalize(transform.GetOrientation() * worldForward); 
			return axes[0];
		}

		inline const glm::vec3 GetSide() const 
		{
			axes[1] = glm::fastNormalize(transform.GetOrientation() * worldSide); 
			return axes[1];
		}
		
		inline const glm::vec3 GetUp() const 
		{
			axes[2] = glm::fastNormalize(transform.GetOrientation() * worldUp); 
			return axes[2];
		}

		// Setters
		virtual inline void SetPosition(const glm::vec3& center) { transform.SetPosition(center); }
		virtual inline void SetScale(const glm::vec3& scale) { transform.SetScale(scale); }
		virtual inline void SetOrientation(const glm::quat& orientation) { transform.SetOrientation(orientation); }
	
	private:
		static int id;

	protected:
		int colliderId;
		ColliderType type;
		bool isConvexShape;
		mutable ObjectAxes axes;
		Transform transform;
	};
}