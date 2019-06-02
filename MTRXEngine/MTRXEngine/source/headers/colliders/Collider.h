/*
	Author: Mohamed Kazma
	Description: A general implementation of a collider
	PS: Calls for collision detection should be done b4 calling the updating functions
*/

#pragma once

#include <Defs.h>
#include <Ray.h>

namespace mtrx
{
	class Collider
	{
	public:	
		Collider(const ColliderType&, const glm::vec3& vec = glm::vec3(), bool isConvex = false);			
		~Collider();										

		virtual bool CheckCollision(const Collider&) = 0;
		virtual bool RaycastCollision(const Ray&) = 0;

		inline const glm::vec3& GetPosition() const { return center; }
		inline const ColliderType& GetColliderType() const { return type; }
		inline const int GetColliderId() const { return colliderId; }
		inline const bool IsConvex() const { return isConvexShape; }

		inline void SetPosition(const glm::vec3& center) { this->center = center; }
		
	private:
		static int id;

	protected:
		glm::vec3 center;
		int colliderId;
		ColliderType type;
		bool isConvexShape;
	};
}