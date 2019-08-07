/*
	Author: Mohamed Kazma
	Description: Util file that includes implementations of collider collision detection
*/

#include <PrecompiledHeader.h>

#include <utils/CollisionUtil.h>
#include <colliders/BoxCollider.h>
#include <colliders/SphereCollider.h>
#include <colliders/CapsuleCollider.h>
#include <colliders/ConvexShapeCollider.h>

namespace mtrx
{
	namespace CollisionUtil
	{
		// Sphere sphere collision detection
		bool SphereSphereCollision(const glm::vec3& center1, const glm::vec3& center2, float radius1, float radius2)
		{
			glm::vec3 diff = center1 - center2;
			float sumRadii = radius1 + radius2;
			std::cout << glm::dot(diff, diff) << " " << sumRadii * sumRadii << std::endl;
			return glm::dot(diff, diff) <= sumRadii * sumRadii;
		}

		// Sphere box collision detection
		bool SphereBoxCollision(const glm::vec3& center1, const glm::vec3& center2, float radius, const glm::vec3* axes, const glm::vec3& halfExtents)
		{
			// Clamp the center to the closest point on the OBB (The same for AABB) then check distance to that box
			glm::vec3 direction = center1 - center2;		// Starting direction
			glm::vec3 closestPoint = center2;

			// For the 3 axes 
			for (int i = 0; i < 3; i++)
			{
				float distance = glm::dot(direction, axes[i]);

				if (distance > halfExtents[i]) distance = halfExtents[i];
				else if (distance < -halfExtents[i]) distance = -halfExtents[i];

				closestPoint += axes[i] * distance;
			}

			// Sphere point collision detection
			glm::vec3 difference = center1 - closestPoint;
			return glm::dot(difference, difference) <= radius * radius;
		}

		// Sphere capsule collision detection
		bool SphereCapsuleCollision(const glm::vec3& center1, const glm::vec3& center2, float radius1, float radius2, const glm::vec3& A, const glm::vec3& B)
		{
			// If the closest point to the sphere's center is of distance less than the radii of the 2 colliders then we have a collision
			glm::vec3 vec;
			return PhysicsUtil::MinDistanceSquaredPointSegment(A, B, center1, vec) <= (radius1 + radius2) * (radius1 + radius2);
		}

		// Sphere mesh Collsion detection
		bool SphereMeshCollision()
		{
			return false;
		}

		// Box Box collision 
		bool BoxBoxCollision(mtrx::BoxCollider& box1, mtrx::BoxCollider& box2)
		{
			return ConvexShapeCollision(box1, box2);
		}

		// Box Capsule collsion detection 
		bool BoxCapsuleCollision(const glm::vec3& center1, const glm::vec3& center2, const glm::vec3& A, const glm::vec3& B, float radius, const glm::vec3* axes, const glm::vec3& halfExtents)
		{
			// Find the closest point on the capsule line to the center of of the box and then do a sphere box collision detection
			glm::vec3 closestPoint;
			PhysicsUtil::MinDistanceSquaredPointSegment(A, B, center1, closestPoint);

			return SphereBoxCollision(closestPoint, center1, radius, axes, halfExtents);
		}

		// Box Mesh collision detection
		bool BoxMeshCollision()
		{
			return false;
		}

		// Capsule Capsule collision detection
		bool CapsuleCapsuleCollision(const glm::vec3& A1, const glm::vec3& B1, const glm::vec3& A2, const glm::vec3& B2, float radius1, float radius2)
		{
			// Min distance between the 2 heights is greater than the sum of the radii
			return PhysicsUtil::MinDistanceSquaredTwoSegments(A1, B1, A2, B2) <= (radius1 + radius2) * (radius1 + radius2);
		}

		// Capsule Mesh Collision detection
		bool CapsuleMeshCollision()
		{
			return false;
		}

		// Mesh Mesh collision detection
		bool MeshMeshCollision()
		{
			return false;
		}

		// Convex Shape convex shape collision detection 
		bool ConvexShapeCollision(mtrx::ConvexShapeCollider& convexCollider1, mtrx::ConvexShapeCollider& convexCollider2)
		{
			return mtrx::GJK::Collision(convexCollider1, convexCollider2);
		}

		// Ray sphere collision detection
		bool RaySphereCollision(const glm::vec3& sphereCenter, float sphereRadius, const glm::vec3& startPointRay, const glm::vec3& rayDirection)
		{
			glm::vec3 closestPoint;
			return PhysicsUtil::MinDistanceSquaredPointRay(sphereCenter, startPointRay, rayDirection, closestPoint) <= sphereRadius * sphereRadius;
		}

		// Ray box collision detection
		bool RayBoxCollision(const glm::vec3& rayStartPosition, const glm::vec3& rayDirection, const glm::vec3& boxCenter, const glm::vec3* axes, const glm::vec3& halfExtents)
		{
			// Sphere box collision but with a sphere of radius 0
			glm::vec3 closestPointRay;
			PhysicsUtil::MinDistanceSquaredPointRay(boxCenter, rayStartPosition, rayDirection, closestPointRay);

			return SphereBoxCollision(closestPointRay, boxCenter, 0, axes, halfExtents);
		}

		// Ray capsuale collision detection
		bool RayCapsuleCollision(const glm::vec3& startPositionRay, const glm::vec3& direction, const glm::vec3& A, const glm::vec3& B, float capsRadius)
		{
			// We only need to find the minimum distance from the ray and line segment and check that with our capsule radius
			return PhysicsUtil::MinDistanceSquaredLineSegmentRay(A, B, startPositionRay, direction) <= capsRadius * capsRadius;
		}

		// Ray Mesh collision detection
		bool RayMeshCollision()
		{
			return false;
		}

		// THIS IS NOT CORRECT CHANGE THISSSSSS!!!!
		// Line segment ray collision detection
		bool LineSegmentRayCollision(const glm::vec3& A, const glm::vec3& B, const glm::vec3& rayStartPoint, const glm::vec3& rayDirection)
		{
			// Hacky solution but it works for the moment MIGHT CHANGE THIS LATER
			// Check if they intersect first (make the longest line segment possible largest value for a float)
			glm::vec3 rayEndPoint = glm::normalize(rayDirection) * std::numeric_limits<float>::infinity();

			// Check for an intersection 
			return PhysicsUtil::MinDistanceSquaredTwoSegments(A, B, rayStartPoint, rayEndPoint) == std::numeric_limits<float>::epsilon();
		}
	}
}