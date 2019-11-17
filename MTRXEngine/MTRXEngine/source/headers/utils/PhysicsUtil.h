#pragma once

#include <math/Ray.h>
#include <utils/CollisionUtil.h>
#include <utils/RaycastCollisionUtil.h>
#include <colliders/Collider.h>

namespace mtrx
{
	namespace PhysicsUtil
	{
		glm::vec3 TripleCross(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c);
		
		float MinDistanceTwoLines(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C, const glm::vec3& D);
		float MinDistanceSquaredTwoSegments(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C, const glm::vec3& D);
		std::pair<float, glm::vec3> MinDistanceSquaredPointRay(const glm::vec3& point, const glm::vec3& startPointRay, const glm::vec3& rayDirection);
		std::pair<float, glm::vec3> MinDistanceSquaredPointSegment(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C);
		float MinDistanceSquaredLineSegmentRay(const glm::vec3& a, const glm::vec3& b, const glm::vec3& rayStart, const glm::vec3& rayDirection);
		
		glm::quat Slerp(const glm::quat& firstRotation, const glm::quat& secondRotation, float t);
		glm::vec3 Lerp(const glm::vec3& startingPosition, const glm::vec3& destination, float t);
		float Ease(float t);
	}
}