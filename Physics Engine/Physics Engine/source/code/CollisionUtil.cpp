/*
	Author: Mohamed Kazma
	Description: Util file that includes implementations of collider collision detection
*/

//I MAYBE SHOULD'T SEND THE ENTIRE COLLIDER MAYBE THE IMPORTANT VALUES!!!! DOING THAT SOON
// And refactor this code

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
	bool SphereSphereCollision(SphereCollider& sphereCollider1, SphereCollider& sphereCollider2)
	{
		Vector3D diff = sphereCollider1.center - sphereCollider2.center;
		return diff.MagnitudeSquared() <= (sphereCollider1.radius + sphereCollider2.radius) * (sphereCollider1.radius + sphereCollider2.radius);
	}

	// Sphere box collision detection
	bool SphereBoxCollision(SphereCollider& sphereCollider, BoxCollider& boxCollider)
	{
		// Check if the sphere's center is inside the box 
		if (sphereCollider.center.x > boxCollider.min.x && sphereCollider.center.x < boxCollider.max.x &&
			sphereCollider.center.y > boxCollider.min.y && sphereCollider.center.y < boxCollider.max.y &&
			sphereCollider.center.z > boxCollider.min.z && sphereCollider.center.z < boxCollider.max.z) return true;
		
		// The sphere is not contained in the box or at least the center is not inside the box
		// Clamp the center to the closest point on the OBB (The same for AABB) then check distance to that box
		Vector3D direction = sphereCollider.center - boxCollider.center;	// Starting direction
		Vector3D closestPoint = boxCollider.center;

		Vector3D u[3];	// Store the axes of the box
		u[0] = boxCollider.sideDirection;		// X-axis
		u[1] = boxCollider.upDirection;			// Y-axis
		u[2] = boxCollider.forwardDirection;	// Z-axis

		// For the 3 axes 
		for (int i = 0; i < 3; i++)
		{
			float distance = direction.DotProduct(u[i]);

			if (distance > boxCollider.halfExtents[i]) distance = boxCollider.halfExtents[i];
			else if (distance < -boxCollider.halfExtents[i]) distance = -boxCollider.halfExtents[i];

			closestPoint += u[i] * distance;
		}

		return (sphereCollider.center - closestPoint).MagnitudeSquared() <= sphereCollider.radius * sphereCollider.radius;
	}

	// Sphere capsule collision detection
	bool SphereCapsuleCollision(SphereCollider& sph , CapsuleCollider& caps)
	{	
		// If the closest point to the sphere's center is of distance less than the radii of the 2 colliders then we have a collision
		return PhysicsUtil::MinDistanceSquaredPointSegment(caps.A , caps.B , sph.center) <= (sph.radius + caps.radii) * (sph.radius * caps.radii);
	}

	bool SphereMeshCollision()
	{
		return false;
	}

	bool BoxBoxCollision(BoxCollider& box1 , BoxCollider& box2)
	{
		return ConvexShapeCollision(box1 , box2);
	}

	bool BoxCapsuleCollision(BoxCollider& box , CapsuleCollider& caps)
	{
		// Find the closest point on the capsule line to the center of of the box and then do a sphere box collision detection
		Vector3D closestPoint;
		PhysicsUtil::MinDistanceSquaredPointSegment(caps.A, caps.B, box.center, closestPoint);
		SphereCollider sph = SphereCollider(closestPoint , caps.radii);			// WILL BE CHANGED SOOON

		return SphereBoxCollision(sph, box);
	}

	bool BoxMeshCollision()
	{
		return false;
	}

	// Capsule Capsule collision detection
	bool CapsuleCapsuleCollision(CapsuleCollider& caps1 , CapsuleCollider& caps2)
	{
		// Min distance between the 2 heights is greater than the sum of the radii
		return PhysicsUtil::MinDistanceSquaredTwoSegments(caps1.A , caps1.B , caps2.A , caps2.B) <= (caps1.radii + caps2.radii) * (caps1.radii + caps2.radii);
	}

	bool CapsuleMeshCollision()
	{
		return false;
	}

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