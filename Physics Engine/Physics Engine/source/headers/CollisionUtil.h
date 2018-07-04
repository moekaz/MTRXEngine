/*
	Author: Mohamed Kazma
	Description: Util file that will include collision detection algorithms
*/

#ifndef COLLISIONUTIL_H
#define COLLISIONUTIL_H

#include <iostream>
#include <vector>

// Forward declarations
class SphereCollider;
class BoxCollider;
class CapsuleCollider;
class MeshCollider;
class ConvexShapeCollider;
class Vector3D;

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
	bool GJK(ConvexShapeCollider&, ConvexShapeCollider&);
	bool UpdateSimplex(std::vector<Vector3D*>& , Vector3D&);
	bool LineSimplexUpdate(std::vector<Vector3D*>&, Vector3D&);
	bool TriangleSimplexUpdate(std::vector<Vector3D*>&, Vector3D&);
	bool TetrahedronSimplexUpdate(std::vector<Vector3D*>&, Vector3D&);
	void EPA();
}
#endif // !COLLISIONUTIL_H
