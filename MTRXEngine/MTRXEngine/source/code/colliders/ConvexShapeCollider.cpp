/*
	Author: Mohamed Kazma
	Description: Implementation of a convex shape collider
*/

#include <PrecompiledHeader.h>
#include <colliders/ConvexShapeCollider.h>

namespace mtrx
{
	ConvexShapeCollider::ConvexShapeCollider(const ColliderType& colliderType, const glm::vec3& center) : Collider(colliderType, center, true) 
	{}

	ConvexShapeCollider::~ConvexShapeCollider() 
	{
		for (int i = 0; i < vertices.size(); ++i)
		{
			delete vertices[i];
		}
	}

	// Used for GJK collision
	glm::vec3 ConvexShapeCollider::Support(const ConvexShapeCollider& convexCollider, const glm::vec3& direction) const
	{
		glm::vec3& p1 = FarthestPointInDirection(direction);
		glm::vec3& p2 = convexCollider.FarthestPointInDirection(-direction);
		glm::vec3 p3 = p1 - p2;
		return p3;
	}

	// Return farthest point with respect to a certain direction
	glm::vec3& ConvexShapeCollider::FarthestPointInDirection(const glm::vec3& direction) const
	{
		float maxDot = -std::numeric_limits<float>::infinity();	// Max dot vector
		glm::vec3* farthest = nullptr;	// Farthest vector

		for (unsigned int i = 0; i < vertices.size(); ++i)
		{
			float dot = glm::dot(*vertices[i], direction);
			if (dot > maxDot)
			{
				maxDot = dot;
				farthest = vertices[i];
			}
		}

		// Check that we have a vertex to use
		assert(farthest);
		return *farthest;
	}

	std::vector<glm::vec3*> ConvexShapeCollider::GetVertices()
	{
		// TODO: implement this
		// Get the vertices of the convex shape with change in position and orientation
		std::vector<glm::vec3*> vertex;
		return vertex;
	}

	// Convex shape collision detection
	bool ConvexShapeCollider::CheckCollision(const Collider& col)
	{
		if (col.IsConvex())
		{
			const ConvexShapeCollider& collider = static_cast<const ConvexShapeCollider&>(col);
			return CollisionUtil::ConvexShapeCollision(*this, collider);	// Collision
		}
		else 
			return false;
	}

	bool ConvexShapeCollider::RaycastCollision(const Ray& ray)
	{
		// A ray is a convex shape if we use it as a line
		glm::vec3 rayEndPoint = glm::normalize(ray.direction) * MAX_RAY_SIZE;	// Get the end point of the ray
		ConvexShapeCollider convexLine = ConvexShapeCollider(ColliderType::ConvexShape, rayEndPoint - ray.startPosition);	// Setup the convex shape
		glm::vec3 start = ray.startPosition;

		//convexLine.vertices.reserve(2);
		//convexLine.vertices.emplace_back(&start);
		//convexLine.vertices.emplace_back(&rayEndPoint);

		return CollisionUtil::ConvexShapeCollision(*this, convexLine);	// Check with GJK 
	}
}