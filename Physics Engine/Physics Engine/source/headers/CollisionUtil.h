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
//class glm::vec3;

// Will document this when it is at least near completion
namespace CollisionUtil
{
	bool SphereSphereCollision(glm::vec3& center1, glm::vec3& center2, float radius1, float radius2);
	bool SphereBoxCollision(glm::vec3& center1, glm::vec3& center2, float radius, glm::vec3& min, glm::vec3& max, glm::vec3* axes[], glm::vec3& halfExtents);
	bool SphereCapsuleCollision(glm::vec3& center1, glm::vec3& center2, float radius1, float radius2, glm::vec3& A, glm::vec3& B);
	bool SphereMeshCollision();
	bool BoxBoxCollision(BoxCollider& , BoxCollider&);
	bool BoxCapsuleCollision(glm::vec3& center1, glm::vec3& center2, glm::vec3& A, glm::vec3& B, float radius, glm::vec3& min, glm::vec3& max, glm::vec3* axes[], glm::vec3& halfExtents);
	bool BoxMeshCollision();
	bool CapsuleCapsuleCollision(glm::vec3& A1, glm::vec3& B1, glm::vec3& A2, glm::vec3& B2, float radius1, float radius2);
	bool CapsuleMeshCollision();
	bool MeshMeshCollision();
	bool ConvexShapeCollision(ConvexShapeCollider& , ConvexShapeCollider&);		// Collision detection between convex shaped colliders
	bool RaySphereCollision(glm::vec3& sphereCenter, float sphereRadius, glm::vec3& startPointRay, glm::vec3& rayDirection);
	bool RayBoxCollision(glm::vec3& rayStartPosition, glm::vec3& rayDirection, glm::vec3& boxCenter, glm::vec3& boxMin, glm::vec3& boxMax, glm::vec3* axes[], glm::vec3& halfExtents);
	bool RayCapsuleCollision(glm::vec3& startPositionRay, glm::vec3& direction, glm::vec3& A, glm::vec3& B, float capsRadius);
	bool RayMeshCollision();
	bool LineSegmentRayCollision(glm::vec3&, glm::vec3&, glm::vec3&, glm::vec3&);
}
#endif // !COLLISIONUTIL_H
