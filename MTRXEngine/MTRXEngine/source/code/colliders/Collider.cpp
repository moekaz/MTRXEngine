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
		Collider(colliderType, Transform(center, orientation, scale), isConvex)
	{}

	// TBD: Axes need to be recalculated
	Collider::Collider(const ColliderType& colliderType, const Transform& transform, bool isConvex) : 
		colliderId(id), type(colliderType), transform(transform), isConvexShape(isConvex)
	{
		++id;
	}
}