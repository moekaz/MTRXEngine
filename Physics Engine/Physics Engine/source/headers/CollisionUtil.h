/*
	Author: Mohamed Kazma
	Description: Util file that will include collision detection algorithms
*/

#pragma once
#ifndef COLLISIONUTIL_H
#define COLLISIONUTIL_H

#include <iostream>
#include <vector>

#include "../headers/Simplex.h"
#include "../headers/GJK.h"

// Forward declarations
class SphereCollider;
class BoxCollider;
class CapsuleCollider;
class MeshCollider;
class ConvexShapeCollider;
class Vector3D;

// Will document this when it is at least near completion
namespace CollisionUtil
{
	bool SphereSphereCollision(SphereCollider& , SphereCollider&);
	bool SphereBoxCollision(SphereCollider& , BoxCollider&);
	bool SphereCapsuleCollision();
	bool SphereMeshCollision();
	bool BoxBoxCollision();
	bool BoxCapsuleCollision();
	bool BoxMeshCollision();
	bool CapsuleCapsuleCollision();
	bool CapsuleMeshCollision();
	bool MeshMeshCollision();
	bool ConvexShapeCollision(ConvexShapeCollider& , ConvexShapeCollider&);		// Collision detection between convex shaped colliders
}
#endif // !COLLISIONUTIL_H
