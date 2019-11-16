#pragma once

#include <math/Ray.h>
#include <utils/CollisionUtil.h>
#include <utils/RaycastCollisionUtil.h>
#include <colliders/Collider.h>

namespace mtrx
{
	namespace PhysicsUtil
	{
		glm::vec3 TripleCross(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c);	// Calculates the triple cross product of 3 vectors
		
		// TBD: NEED TO REFACTOR ALL OF THIS CODE 
		bool LineIntersect(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, const glm::vec3& d, glm::vec3& intersection);
		bool LineSegmentIntersect(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, const glm::vec3& d, glm::vec3& intersection);
		bool LineRayIntersect(const glm::vec3& a, const glm::vec3& b, const glm::vec3& rayStart, const glm::vec3& rayDirection, glm::vec3& intersection);
		bool LineSegmentRayIntersect(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, const glm::vec3& d, glm::vec3& intersection);
		
		float MinDistanceTwoLines(const glm::vec3&, const glm::vec3&, const glm::vec3&, const glm::vec3&, glm::vec3* intersection);	// Minimum distance between 2 lines squared
		float MinDistanceSquaredTwoSegments(const glm::vec3&, const glm::vec3&, const glm::vec3&, const glm::vec3&);	// Minimum distance between 2 line segments squared
		float MinDistanceSquaredPointSegment(const glm::vec3&, const glm::vec3&, const glm::vec3&, glm::vec3&);	// Minimum ditance between a point and a line segment squared
		float MinDistanceSquaredPointRay(const glm::vec3&, const glm::vec3&, const glm::vec3&, glm::vec3&);	// Minimum distance between a point and a ray squared
		float MinDistanceSquaredLineRay(const glm::vec3& A, const glm::vec3& B, const glm::vec3& rayStart, const glm::vec3& rayDirection, glm::vec3* intersection);
		float MinDistanceSquaredLineSegmentRay(const glm::vec3&, const glm::vec3&, const glm::vec3&, const glm::vec3&);	// Minimum distance between a line segment and a ray squared
		
		glm::quat Slerp(const glm::quat& firstRotation, const glm::quat& secondRotation, float t);	// Linear interpolation of a rotation (Quaternions)
		glm::vec3 Lerp(const glm::vec3& startingPosition, const glm::vec3& destination, float t);	// Linear interpolation along a line segment
		float Ease(float t);	// Easing a float along a half sin curve to simulate acceleration
	}
}