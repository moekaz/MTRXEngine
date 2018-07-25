/*
	Author: Mohamed Kazma
	Description: Implementation of a convex shape collider
*/

#include "../headers/ConvexShapeCollider.h"

ConvexShapeCollider::ConvexShapeCollider(const Vector3D& center) : Collider(center)
{
	isConvexShape = true;
}

ConvexShapeCollider::~ConvexShapeCollider(){}

// Used for GJK collision
Vector3D& ConvexShapeCollider::Support(ConvexShapeCollider& convexCollider , Vector3D& direction)
{
	Vector3D& p1 = FarthestPointInDirection(direction);
	Vector3D neg = -direction;
	Vector3D& p2 = convexCollider.FarthestPointInDirection(neg);
	Vector3D p3 = p1 - p2;
	return p3;
}

// Return farthest point with respect to a certain direction
Vector3D& ConvexShapeCollider::FarthestPointInDirection(Vector3D& direction)
{
	float maxDot = -std::numeric_limits<float>::infinity();	// Max dot vector
	Vector3D *farthest = NULL;	// Farthest vector

	for (int i = 0; i < vertices.size(); i++)
	{
		float dot = vertices[i]->DotProduct(direction);
		if (dot > maxDot)
		{
			maxDot = dot;
			farthest = vertices[i];
		}
	}
	
	return *farthest;
}

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

void ConvexShapeCollider::Update(const Vector3D& center)
{
	this->center = center;
}