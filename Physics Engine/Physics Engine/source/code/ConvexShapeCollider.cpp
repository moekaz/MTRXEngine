/*
	Author: Mohamed Kazma
	Description: Implementation of a convex shape collider
*/

#include "../headers/ConvexShapeCollider.h"

// Constructor
ConvexShapeCollider::ConvexShapeCollider(const glm::vec3& center) : Collider(center)
{
	type = ColliderType::ConvexShape;	// This is a convex shape
	isConvexShape = true;
}

//Destructor
ConvexShapeCollider::~ConvexShapeCollider(){}

// Used for GJK collision
glm::vec3 ConvexShapeCollider::Support(ConvexShapeCollider& convexCollider , glm::vec3& direction)
{
	glm::vec3& p1 = FarthestPointInDirection(direction);
	glm::vec3 neg = -direction;
	glm::vec3& p2 = convexCollider.FarthestPointInDirection(neg);
	glm::vec3 p3 = p1 - p2;
	return p3;
}

// Return farthest point with respect to a certain direction
glm::vec3& ConvexShapeCollider::FarthestPointInDirection(glm::vec3& direction)
{
	float maxDot = -std::numeric_limits<float>::infinity();	// Max dot vector
	glm::vec3 *farthest = NULL;	// Farthest vector

	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		float dot = glm::dot(*vertices[i] , direction); //vertices[i]->DotProduct(direction);
		if (dot > maxDot)
		{
			maxDot = dot;
			farthest = vertices[i];
		}
	}
	
	return *farthest;
}

// Convex shape collision detection
bool ConvexShapeCollider::CheckCollision(Collider& col)
{
	ConvexShapeCollider& collider = static_cast<ConvexShapeCollider&>(col);

	if (col.isConvexShape) 
	{
		UpdateCollisionInfo();
		return CollisionUtil::ConvexShapeCollision(*this, collider);	// Collision
	}
	else return false;	// Its not a convex hull
}

// Updating the values of a convex shape
void ConvexShapeCollider::Update(const glm::vec3& center)
{
	this->center = center;
}

// We do not have an implementation of this
bool ConvexShapeCollider::RaycastCollision(Ray& ray) 
{
	// A ray is a convex shape if we use it as a line
	glm::vec3 rayEndPoint = glm::normalize(ray.direction) * std::numeric_limits<float>::infinity();	// Get the end point of the ray
	ConvexShapeCollider convexLine = ConvexShapeCollider(rayEndPoint - ray.startPosition);	// Setup the convex shape
	convexLine.vertices = { &ray.startPosition , &rayEndPoint };	// Set the vertices to be the 2 points of the ray

	return CollisionUtil::ConvexShapeCollision(*this , convexLine);	// Check with GJK 
}