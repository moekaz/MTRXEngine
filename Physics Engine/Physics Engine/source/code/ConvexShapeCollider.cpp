/*
	Author: Mohamed Kazma
	Description: 
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
	Vector3D neg = direction - (direction * 2.0f);
	Vector3D& p2 = convexCollider.FarthestPointInDirection(neg);	
	Vector3D p3 = p1 - p2;
	return p3;
}

// Return farthest point with respect to a certain direction
Vector3D& ConvexShapeCollider::FarthestPointInDirection(Vector3D& direction)
{
	Vector3D& farthest = *vertices[0];	// Farthest vector
	float maxDot = farthest.DotProduct(direction);	// maximum dot product according to the direction

	for (int i = 1; i < vertices.size(); i++)
	{
		float dot = vertices[i]->DotProduct(direction);
		if (dot > maxDot)
		{
			maxDot = dot;
			farthest = *vertices[i];
		}
	}

	return farthest;
}

bool ConvexShapeCollider::CheckCollision(Collider& col)
{
	ConvexShapeCollider& collider = static_cast<ConvexShapeCollider&>(col);
	if (col.isConvexShape) return CollisionUtil::GJK(*this , collider);	// collision
	else return false;	// Its not a convex hull
	//return false;
}

void ConvexShapeCollider::Update(const Vector3D& center)
{
	this->center = center;
}