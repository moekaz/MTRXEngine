/*
	Author: Mohamed Kazma
	Description: Utility file that would include general functions that can be useful for general use
*/

#pragma once

#include <Ray.h>
#include <CollisionUtil.h>
#include <Collider.h>

namespace MTRX
{
	namespace PhysicsUtil
	{
		glm::vec3 TripleCross(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c);	// Calculates the triple cross product of 3 vectors
		float MinDistanceTwoLines(const glm::vec3&, const glm::vec3&, const glm::vec3&, const glm::vec3&);	// Minimum distance between 2 lines squared
		float MinDistanceSquaredTwoSegments(const glm::vec3&, const glm::vec3&, const glm::vec3&, const glm::vec3&);	// Minimum distance between 2 line segments squared
		float MinDistanceSquaredPointSegment(const glm::vec3&, const glm::vec3&, const glm::vec3&, glm::vec3&);	// Minimum ditance between a point and a line segment squared
		float MinDistanceSquaredPointRay(const glm::vec3&, const glm::vec3&, const glm::vec3&, glm::vec3&);	// Minimum distance between a point and a ray squared
		float MinDistanceSquaredLineSegmentRay(const glm::vec3&, const glm::vec3&, const glm::vec3&, const glm::vec3&);	// Minimum distance between a line segment and a ray squared
		Collider* RaycastFiltered(const std::map<int, Collider*>& colliders, const std::vector<Collider*>& filterColliders, const glm::vec3& rayStartPosition, const glm::vec3& rayDirection);	// Raycast check on colliders filtered
		Collider* RaycastUnfiltered(const std::map<int, Collider*>& colliders, const glm::vec3& rayStartPosition, const glm::vec3& rayDirection);	// Raycast check for all colliders
		glm::quat Slerp(const glm::quat& firstRotation, const glm::quat& secondRotation, float t);	// Linear interpolation of a rotation (Quaternions)
		glm::vec3 Lerp(const glm::vec3& startingPosition, const glm::vec3& destination, float t);	// Linear interpolation along a line segment
		float Ease(float t);	// Easing a float along a half sin curve to simulate acceleration
	}
}