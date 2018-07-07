/*
	Author: Mohamed Kazma
	Description: Util file that includes implementations of collider collision detection
*/

// Fix for cyclic dependencies
#include "../headers/CollisionUtil.h"
#include "../headers/BoxCollider.h"
#include "../headers/SphereCollider.h"
//#include "../headers/CapsuleCollider.h"
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

	bool CapsuleCapsuleCollision()
	{
		return false;
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