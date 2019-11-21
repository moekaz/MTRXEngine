/*
	Author: Mohamed Kazma
	Description: Some general implementation of all colliders
*/

#include <PrecompiledHeader.h>
#include <colliders/Collider.h>

namespace mtrx
{
	int Collider::id = 0;

	Collider::Collider(const ColliderType& colliderType, const glm::vec3& center, const glm::quat& orientation, const glm::vec3& scale , bool isConvex) :
		colliderId(id), type(colliderType), transform(center, orientation, scale), isConvexShape(isConvex), 
		axes(glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), glm::vec3(0, 0, -1))
	{
		++id;
	}

	Collider::Collider(const ColliderType& colliderType, const Transform& transform, bool isConvex) : 
		colliderId(id), type(colliderType), transform(transform), isConvexShape(isConvex), 
		axes(glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), glm::vec3(0, 0, -1))
	{
		++id;
	}
}