/*
	Author: Mohamed Kazma
	Description: Util file that includes implementations of collider collision detection
*/

//I MAYBE SHOULD'T SEND THE ENTIRE COLLIDER MAYBE THE IMPORTANT VALUES!!!!

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
		return false;
	}

	bool SphereCapsuleCollision()
	{
		return false;
	}

	bool SphereMeshCollision()
	{
		return false;
	}

	bool CollisionUtil::BoxBoxCollision()
	{
		return false;
	}

	bool BoxCapsuleCollision()
	{
		return false;
	}

	bool BoxMeshCollision()
	{
		return false;
	}

	// Capsule Capsule collision detection
	bool CapsuleCapsuleCollision(CapsuleCollider& caps1 , CapsuleCollider& caps2)
	{
		// Min distance between the 2 heights is greater than the sum of the radii
		return Utils::MinDistanceSquaredTwoSegments(caps1.A , caps1.B , caps2.A , caps2.B) <= (caps1.radii + caps2.radii) * (caps1.radii + caps2.radii);
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