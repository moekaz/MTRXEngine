/*
	Author: Mohamed Kazma
	Description: Util file that will include collision detection algorithms
*/

#ifndef COLLISIONUTIL_H
#define COLLISIONUTIL_H

#include <iostream>

class SphereCollider;
class BoxCollider;
class CapsuleCollider;
class MeshCollider;

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
}
#endif // !COLLISIONUTIL_H
