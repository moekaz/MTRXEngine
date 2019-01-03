/*
	Author: Mohamed Kazma
	Description: Util file that will include collision detection algorithms
*/

#pragma once

#include <Simplex.h>
#include <GJK.h>
#include <PhysicsUtil.h>

namespace MTRX
{
	// Forward declarations
	class BoxCollider;
	class MeshCollider;
	class ConvexShapeCollider;

	namespace CollisionUtil
	{
		bool SphereSphereCollision(const glm::vec3& center1, const glm::vec3& center2, float radius1, float radius2);
		bool SphereBoxCollision(const glm::vec3& center1, const glm::vec3& center2, float radius, const glm::vec3& min, const glm::vec3& max, const std::vector<glm::vec3*>& axes, const glm::vec3& halfExtents);
		bool SphereCapsuleCollision(const glm::vec3& center1, const glm::vec3& center2, float radius1, float radius2, const glm::vec3& A, const glm::vec3& B);
		bool SphereMeshCollision();
		bool BoxBoxCollision(const MTRX::BoxCollider&, const MTRX::BoxCollider&);
		bool BoxCapsuleCollision(const glm::vec3& center1, const glm::vec3& center2, const glm::vec3& A, const glm::vec3& B, float radius, const glm::vec3& min, const glm::vec3& max, const std::vector<glm::vec3*>& axes, const glm::vec3& halfExtents);
		bool BoxMeshCollision();
		bool CapsuleCapsuleCollision(const glm::vec3& A1, const glm::vec3& B1, const glm::vec3& A2, const glm::vec3& B2, float radius1, float radius2);
		bool CapsuleMeshCollision();
		bool MeshMeshCollision();
		bool ConvexShapeCollision(const MTRX::ConvexShapeCollider&, const MTRX::ConvexShapeCollider&);		// Collision detection between convex shaped colliders
		bool RaySphereCollision(const glm::vec3& sphereCenter, float sphereRadius, const glm::vec3& startPointRay, const glm::vec3& rayDirection);
		bool RayBoxCollision(const glm::vec3& rayStartPosition, const glm::vec3& rayDirection, const glm::vec3& boxCenter, const glm::vec3& boxMin, const glm::vec3& boxMax, const std::vector<glm::vec3*>& axes, const glm::vec3& halfExtents);
		bool RayCapsuleCollision(const glm::vec3& startPositionRay, const glm::vec3& direction, const glm::vec3& A, const glm::vec3& B, float capsRadius);
		bool RayMeshCollision();
		bool LineSegmentRayCollision(const glm::vec3&, const glm::vec3&, const glm::vec3&, const glm::vec3&);
	}
}