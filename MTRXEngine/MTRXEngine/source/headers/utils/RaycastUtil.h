#pragma once

#include <colliders/Collider.h>
#include <utils/PhysicsUtil.h>
#include <utils/CollisionUtil.h>
#include <math/Ray.h>

namespace mtrx
{
	namespace RaycastUtil
	{
		bool RaySphereCollision(const glm::vec3& sphereCenter, float sphereRadius, const glm::vec3& startPointRay, const glm::vec3& rayDirection);
		bool RayBoxCollision(const glm::vec3& rayStartPosition, const glm::vec3& rayDirection, const glm::vec3& boxCenter, const glm::vec3* axes, const glm::vec3& halfExtents);
		bool RayCapsuleCollision(const glm::vec3& startPositionRay, const glm::vec3& direction, const glm::vec3& A, const glm::vec3& B, float capsRadius);
		bool RayMeshCollision();
		bool LineSegmentRayCollision(const glm::vec3&, const glm::vec3&, const glm::vec3&, const glm::vec3&);
		Collider* RaycastFiltered(const std::map<int, Collider*>& colliders, const std::vector<Collider*>& filterColliders, const glm::vec3& rayStartPosition, const glm::vec3& rayDirection);	// Raycast check on colliders filtered
		Collider* RaycastUnfiltered(const std::map<int, Collider*>& colliders, const glm::vec3& rayStartPosition, const glm::vec3& rayDirection);	// Raycast check for all colliders
	}
}