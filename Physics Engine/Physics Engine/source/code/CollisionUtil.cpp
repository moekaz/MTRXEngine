/*
	Author: Mohamed Kazma
	Description: Util file that includes implementations of collider collision detection
*/

#include "../headers/CollisionUtil.h"
#include "../headers/BoxCollider.h"
#include "../headers/SphereCollider.h"
//#include "../headers/CapsuleCollider.h"
//#include "../headers/MeshCollider.h"

namespace CollisionUtil
{
	// Sphere sphere collision detection
	bool CollisionUtil::SphereSphereCollision(SphereCollider& sphereCollider1 , SphereCollider& sphereCollider2)
	{
		Vector3D diff = sphereCollider1.center - sphereCollider2.center;
		return diff.MagnitudeSquared() <= (sphereCollider1.radius + sphereCollider2.radius) * (sphereCollider1.radius + sphereCollider2.radius);
	}

	// Sphere box collision detection
	bool CollisionUtil::SphereBoxCollision(SphereCollider& sphereCollider , BoxCollider& boxCollider)
	{
		return false;
	}

	bool CollisionUtil::SphereCapsuleCollision()
	{
		return false;
	}

	bool CollisionUtil::SphereMeshCollision()
	{
		return false;
	}

	bool CollisionUtil::BoxBoxCollision()
	{
		return false;
	}

	bool CollisionUtil::BoxCapsuleCollision()
	{
		return false;
	}

	bool CollisionUtil::BoxMeshCollision()
	{
		return false;
	}

	bool CollisionUtil::CapsuleCapsuleCollision()
	{
		return false;
	}

	bool CollisionUtil::CapsuleMeshCollision()
	{
		return false;
	}

	bool CollisionUtil::MeshMeshCollision()
	{
		return false;
	}
}