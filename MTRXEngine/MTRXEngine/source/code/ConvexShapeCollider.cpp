/*
	Author: Mohamed Kazma
	Description: Implementation of a convex shape collider
*/

#include <PrecompiledHeader.h>
#include <ConvexShapeCollider.h>

namespace MTRX
{
	// Constructor
	ConvexShapeCollider::ConvexShapeCollider(const ColliderType& colliderType, const glm::vec3& center) : Collider(colliderType, center, true) {}

	//Destructor
	ConvexShapeCollider::~ConvexShapeCollider() {}

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
		glm::vec3* farthest = NULL;	// Farthest vector

		for (unsigned int i = 0; i < vertices.size(); i++)
		{
			float dot = glm::dot(*vertices[i], direction);
			if (dot > maxDot)
			{
				maxDot = dot;
				farthest = vertices[i];
			}
		}

		assert(farthest);	// Check that we have a vertex to use
		return *farthest;
	}

	// Convex shape collision detection
	bool ConvexShapeCollider::CheckCollision(const Collider& col)
	{
		const ConvexShapeCollider& collider = static_cast<const ConvexShapeCollider&>(col);

		if (col.isConvexShape)
		{
			UpdateCollisionInfo();
			return CollisionUtil::ConvexShapeCollision(*this, collider);	// Collision
		}
		else return false;	// Its not a convex hull
	}

	// Updating the values of a convex shape
	void ConvexShapeCollider::PhysicsUpdate() {}

	bool ConvexShapeCollider::RaycastCollision(const Ray& ray)
	{
		// A ray is a convex shape if we use it as a line
		glm::vec3 rayEndPoint = glm::normalize(ray.direction) * std::numeric_limits<float>::infinity();	// Get the end point of the ray
		ConvexShapeCollider convexLine = ConvexShapeCollider(ColliderType::ConvexShape, rayEndPoint - ray.startPosition);	// Setup the convex shape
		glm::vec3 start = ray.startPosition;

		convexLine.vertices.reserve(2);
		convexLine.vertices.emplace_back(&start);
		convexLine.vertices.emplace_back(&rayEndPoint);

		return CollisionUtil::ConvexShapeCollision(*this, convexLine);	// Check with GJK 
	}
}