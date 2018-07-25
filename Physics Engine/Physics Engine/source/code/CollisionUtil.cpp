/*
	Author: Mohamed Kazma
	Description: Util file that includes implementations of collider collision detection
*/

// Fix for cyclic dependencies
#include "../headers/CollisionUtil.h"
#include "../headers/BoxCollider.h"
#include "../headers/SphereCollider.h"
#include "../headers/CapsuleCollider.h"
//#include "../headers/MeshCollider.h"
#include "../headers/ConvexShapeCollider.h"
#include "../headers/Vector3D.h"

namespace CollisionUtil
{
	// Sphere sphere collision detection
	bool SphereSphereCollision(Vector3D& center1, Vector3D& center2 , float radius1 , float radius2)
	{
		Vector3D diff = center1 - center2;
		float sumRadii = radius1 + radius2;
		return diff.MagnitudeSquared() <= sumRadii * sumRadii;
	}

	// Sphere box collision detection
	bool SphereBoxCollision(Vector3D& center1 , Vector3D& center2 , float radius , Vector3D& min , Vector3D& max , std::vector<Vector3D>& axes , Vector3D& halfExtents)
	{
		// Check if the sphere's center is inside the box 
		if (center1.x > min.x && center1.x < max.x &&
			center1.y > min.y && center1.y < max.y &&
			center1.z > min.z && center1.z < max.z) return true;
		
		// The sphere is not contained in the box or at least the center is not inside the box
		// Clamp the center to the closest point on the OBB (The same for AABB) then check distance to that box
		Vector3D direction = center1 - center2;		// Starting direction
		Vector3D closestPoint = center2;

		// For the 3 axes 
		for (int i = 0; i < 3; i++)
		{
			float distance = direction.DotProduct(axes[i]);

			if (distance > halfExtents[i]) distance = halfExtents[i];
			else if (distance < -halfExtents[i]) distance = -halfExtents[i];

			closestPoint += axes[i] * distance;
		}

		// Sphere point collision detection
		return (center1 - closestPoint).MagnitudeSquared() <= radius * radius;
	}

	// Sphere capsule collision detection
	bool SphereCapsuleCollision(Vector3D& center1 , Vector3D& center2 ,float radius1 , float radius2 , Vector3D& A , Vector3D& B)
	{	
		// If the closest point to the sphere's center is of distance less than the radii of the 2 colliders then we have a collision
		Vector3D vec;
		return PhysicsUtil::MinDistanceSquaredPointSegment(A , B , center1 , vec) <= (radius1 + radius2) * (radius1 * radius2);
	}

	// Sphere mesh Collsiion detection
	bool SphereMeshCollision()
	{
		return false;
	}

	// Box Box collision 
	bool BoxBoxCollision(BoxCollider& box1 , BoxCollider& box2)
	{
		return ConvexShapeCollision(box1 , box2);
	}

	// Box Capsule collsiion detection 
	bool BoxCapsuleCollision(Vector3D& center1, Vector3D& center2, Vector3D& A, Vector3D& B, float radius, Vector3D& min, Vector3D& max, std::vector<Vector3D>& axes, Vector3D& halfExtents)
	{
		// Find the closest point on the capsule line to the center of of the box and then do a sphere box collision detection
		Vector3D closestPoint;
		PhysicsUtil::MinDistanceSquaredPointSegment(A, B, center1, closestPoint);

		return SphereBoxCollision(center2, center1, radius, min, max, axes, halfExtents);
	}

	// Box Mesh collision detection
	bool BoxMeshCollision()
	{
		return false;
	}

	// Capsule Capsule collision detection
	bool CapsuleCapsuleCollision(Vector3D& A1 , Vector3D& B1 , Vector3D& A2 , Vector3D& B2 , float radius1 , float radius2)
	{
		// Min distance between the 2 heights is greater than the sum of the radii
		return PhysicsUtil::MinDistanceSquaredTwoSegments(A1 , B1 , A2 , B2) <= (radius1 + radius2) * (radius1 + radius2);
	}
		
	// Capsule Mesh Collision detection
	bool CapsuleMeshCollision()
	{
		return false;
	}

	// Mesh Mesh collision detection
	bool MeshMeshCollision()
	{
		return false;
	}

	// Convex Shape convex shape collision detection 
	bool ConvexShapeCollision(ConvexShapeCollider& convexCollider1, ConvexShapeCollider& convexCollider2)
	{
		return GJK().GJKCollision(convexCollider1 , convexCollider2);
	}
}