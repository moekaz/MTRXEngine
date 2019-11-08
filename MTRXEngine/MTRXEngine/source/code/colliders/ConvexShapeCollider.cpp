/*
	Author: Mohamed Kazma
	Description: Implementation of a convex shape collider
*/

#include <PrecompiledHeader.h>
#include <colliders/ConvexShapeCollider.h>

namespace mtrx
{
	ConvexShapeCollider::ConvexShapeCollider(const ColliderType& colliderType, const glm::vec3& center, const glm::quat& orientation, const glm::vec3& scale) : 
		Collider(colliderType, center, orientation, scale, true), transformModified(true)
	{}

	ConvexShapeCollider::ConvexShapeCollider(const ColliderType& colliderType, const Transform& transform) : 
		Collider(colliderType, transform, true), transformModified(true)
	{}

	ConvexShapeCollider::~ConvexShapeCollider()
	{
		for (int i = 0; i < vertices.size(); ++i)
		{
			delete vertices[i];
			delete transformedVertices[i];
		}
	}

	// Convex shape collision detection
	bool ConvexShapeCollider::CheckCollision(const Collider& col)
	{
		// TBD: THIS IS NOT GOOD AT ALL (AS IT WILL BREAK COLLISION)
		if (col.IsConvex())
		{
			ConvexShapeCollider& collider = static_cast<ConvexShapeCollider&>(const_cast<Collider&>(col));
			auto vertices1 = GetVertices();
			auto vertices2 = collider.GetVertices();
			return CollisionUtil::ConvexShapeCollision(vertices1->begin(), vertices1->end(), vertices2->begin(), vertices2->end());
		}
		else 
			return false;
	}

	bool ConvexShapeCollider::RaycastCollision(const Ray& ray)
	{
		// TBD: LOOK INTO WHETHER WE CAN DO A PROPER RAYCAST ON ANY CONVEX SHAPE
		// A ray is a convex shape if we use it as a line segment
		glm::vec3 rayEndPoint = glm::fastNormalize(ray.direction) * MAX_RAY_SIZE;	// Get the end point of the ray
		ConvexShapeCollider convexLine = ConvexShapeCollider(ColliderType::ConvexShape, (rayEndPoint - ray.startPosition) * 0.5f);	// Setup the convex shape

		std::array<glm::vec3*, 2> verts1 = { const_cast<glm::vec3*>(&ray.startPosition), &rayEndPoint };
		auto verts2 = GetVertices();

		return CollisionUtil::ConvexShapeCollision(verts1.begin(), verts1.begin(), verts2->begin(), verts2->end());
	}

	glm::mat4 ConvexShapeCollider::GetModelMatrix() const
	{
		glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f), GetPosition());
		glm::mat4 rotateMatrix = glm::toMat4(GetOrientation());
		glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), GetScale());

		// ISROT
		return translateMatrix * rotateMatrix * scaleMatrix;
	}

	std::vector<glm::vec3*>* ConvexShapeCollider::GetVertices() const
	{
		// If the collider was not modified no need to redo transform operation
		if (!transformModified)
			return &transformedVertices;

		glm::mat4 modelMatrix = GetModelMatrix();
		for (int i = 0; i < vertices.size(); ++i)
		{
			glm::vec4 vec = modelMatrix * glm::vec4(*vertices[i], 1.f);
			transformedVertices[i]->x = vec.x;
			transformedVertices[i]->y = vec.y;
			transformedVertices[i]->z = vec.z;
		}

		transformModified = false;
		return &transformedVertices;
	}
}