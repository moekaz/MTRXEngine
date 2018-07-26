/*
	Author: Mohamed Kazma
	Description: Util file that will include collision detection algorithms
*/

#pragma once
#ifndef COLLISIONUTIL_H
#define COLLISIONUTIL_H

#include <iostream>
#include <vector>
#include <glm/vec3.hpp>

#include "../headers/Simplex.h"
#include "../headers/GJK.h"
#include "../headers/PhysicsUtil.h"

// Forward declarations
class SphereCollider;
class BoxCollider;
class CapsuleCollider;
class MeshCollider;
class ConvexShapeCollider;
//class Vector3D;

// Will document this when it is at least near completion
namespace CollisionUtil
{
	bool SphereSphereCollision(glm::vec3& center1, glm::vec3& center2, float radius1, float radius2);
	bool SphereBoxCollision(glm::vec3& center1, glm::vec3& center2, float radius, glm::vec3& min, glm::vec3& max, std::vector<glm::vec3>& axes, glm::vec3& halfExtents);
	bool SphereCapsuleCollision(Vector3D& center1, Vector3D& center2, float radius1, float radius2, Vector3D& A, Vector3D& B);
	bool SphereMeshCollision();
	bool BoxBoxCollision(BoxCollider& , BoxCollider&);
	bool BoxCapsuleCollision(Vector3D& center1, Vector3D& center2, Vector3D& A, Vector3D& B, float radius, Vector3D& min, Vector3D& max, std::vector<Vector3D>& axes, Vector3D& halfExtents);
	bool BoxMeshCollision();
	bool CapsuleCapsuleCollision(Vector3D& A1, Vector3D& B1, Vector3D& A2, Vector3D& B2, float radius1, float radius2);
	bool CapsuleMeshCollision();
	bool MeshMeshCollision();
	bool ConvexShapeCollision(ConvexShapeCollider& , ConvexShapeCollider&);		// Collision detection between convex shaped colliders
}
#endif // !COLLISIONUTIL_H
