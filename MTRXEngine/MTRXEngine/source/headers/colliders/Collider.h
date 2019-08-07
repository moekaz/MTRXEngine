/*
	Author: Mohamed Kazma
	Description: A general implementation of a collider
	PS: Calls for collision detection should be done b4 calling the updating functions
*/

#pragma once

#include <Defs.h>
#include <Ray.h>
#include <math/Transform.h>

namespace mtrx
{
	class Collider
	{
	public:	
		Collider(const ColliderType& colliderType, const glm::vec3& center = glm::vec3(), const glm::quat& orientation = glm::angleAxis(0.f, glm::vec3(0, 1, 0)), const glm::vec3& scale = glm::vec3(1, 1, 1), bool isConvex = false);
		Collider(const ColliderType& colliderType, const Transform& transform, bool isConvex = false);
		~Collider();										
		
		virtual bool CheckCollision(const Collider&) = 0;
		virtual bool RaycastCollision(const Ray&) = 0;

		// Getters
		inline const glm::vec3& GetPosition() const { return transform.GetPosition(); }
		inline const glm::vec3& GetScale() const { return transform.GetScale(); }
		inline const glm::quat& GetOrientation() const { return transform.GetOrientation(); }
		inline const ColliderType& GetColliderType() const { return type; }
		inline const int GetColliderId() const { return colliderId; }
		inline const bool IsConvex() const { return isConvexShape; }

		inline glm::vec3 GetForward() { return glm::fastNormalize(transform.GetOrientation() * axes[0]); }
		inline glm::vec3 GetSide() { return glm::fastNormalize(transform.GetOrientation() * axes[1]); }
		inline glm::vec3 GetUp() { return glm::fastNormalize(transform.GetOrientation() * axes[2]); }

		// Setters
		virtual inline void SetPosition(const glm::vec3& center) { transform.SetPosition(center); }
		virtual inline void SetScale(const glm::vec3& scale) { transform.SetScale(scale); }
		virtual inline void SetOrientation(const glm::quat& orientation) { transform.SetOrientation(orientation); }
	
	private:
		static int id;
		Transform transform; // position orientaion and scale of the collider

	protected:
		int colliderId; // The id of collider
		ColliderType type; // The collider type
		bool isConvexShape; // Whether it is a convex shape collider or not
		ObjectAxes axes; // The axes that define this collider's world
	};
}