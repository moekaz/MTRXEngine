/*
	Author: Mohamed Kazma
	Description: Some general implementation of all colliders
*/

#include <PrecompiledHeader.h>
#include <colliders/Collider.h>

namespace mtrx
{
	int Collider::id = 0;	// Set the value of the static int id 

	Collider::Collider(const ColliderType& colliderType, const glm::vec3& vec, bool isConvex) : colliderId(id), center(vec), type(colliderType),
		isConvexShape(isConvex)
	{
		++id;
	}

	Collider::~Collider()
	{}
}