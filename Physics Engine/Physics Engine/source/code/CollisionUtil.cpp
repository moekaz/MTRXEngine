/*
	Author: Mohamed Kazma
	Description: Util file that includes implementations of collider collision detection
*/

// Fix for cyclic dependencies
#include "../headers/CollisionUtil.h"
#include "../headers/BoxCollider.h"
#include "../headers/SphereCollider.h"
#include "../headers/CapsuleCollider.h"
//#include "../headers/MeshCollider.h"
#include "../headers/ConvexShapeCollider.h"

namespace CollisionUtil
{
	// Sphere sphere collision detection
	bool SphereSphereCollision(glm::vec3& center1, glm::vec3& center2 , float radius1 , float radius2)
	{
		glm::vec3 diff = center1 - center2;
		float sumRadii = radius1 + radius2;
		return glm::dot(diff , diff) <= sumRadii * sumRadii;
	}

	// Sphere box collision detection
	bool SphereBoxCollision(glm::vec3& center1 , glm::vec3& center2 , float radius , glm::vec3& min , glm::vec3& max , std::vector<glm::vec3>& axes , glm::vec3& halfExtents)
	{	
		// The sphere is not contained in the box or at least the center is not inside the box
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
		return glm::dot(difference , difference) <= radius * radius;
	}

	// Sphere capsule collision detection
	bool SphereCapsuleCollision(glm::vec3& center1 , glm::vec3& center2 ,float radius1 , float radius2 , glm::vec3& A , glm::vec3& B)
	{	
		// If the closest point to the sphere's center is of distance less than the radii of the 2 colliders then we have a collision
		glm::vec3 vec;
		return PhysicsUtil::MinDistanceSquaredPointSegment(A , B , center1 , vec) <= (radius1 + radius2) * (radius1 + radius2);
	}

	// Sphere mesh Collsiion detection
	bool SphereMeshCollision()
	{
		return false;
	}

	// Box Box collision 
	bool BoxBoxCollision(BoxCollider& box1 , BoxCollider& box2)
	{
		return ConvexShapeCollision(box1 , box2);
	}

	// Box Capsule collsiion detection 
	bool BoxCapsuleCollision(glm::vec3& center1, glm::vec3& center2, glm::vec3& A, glm::vec3& B, float radius, glm::vec3& min, glm::vec3& max, std::vector<glm::vec3>& axes, glm::vec3& halfExtents)
	{
		// Find the closest point on the capsule line to the center of of the box and then do a sphere box collision detection
		glm::vec3 closestPoint;
		PhysicsUtil::MinDistanceSquaredPointSegment(A, B, center1, closestPoint);

		return SphereBoxCollision(closestPoint, center1, radius, min, max, axes, halfExtents);
	}

	// Box Mesh collision detection
	bool BoxMeshCollision()
	{
		return false;
	}

	// Capsule Capsule collision detection
	bool CapsuleCapsuleCollision(glm::vec3& A1 , glm::vec3& B1 , glm::vec3& A2 , glm::vec3& B2 , float radius1 , float radius2)
	{
		// Min distance between the 2 heights is greater than the sum of the radii
		return PhysicsUtil::MinDistanceSquaredTwoSegments(A1 , B1 , A2 , B2) <= (radius1 + radius2) * (radius1 + radius2);
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
	bool ConvexShapeCollision(ConvexShapeCollider& convexCollider1, ConvexShapeCollider& convexCollider2)
	{
		return GJK().GJKCollision(convexCollider1 , convexCollider2);
	}

	// Ray sphere collision detection
	bool RaySphereCollision(glm::vec3& sphereCenter , float sphereRadius, glm::vec3& startPointRay , glm::vec3& rayDirection)
	{
		glm::vec3 closestPoint;
		return PhysicsUtil::MinDistanceSquaredPointRay(sphereCenter , startPointRay , rayDirection , closestPoint) <= sphereRadius * sphereRadius;
	}

	// Ray box collision detection
	bool RayBoxCollision(glm::vec3& rayStartPosition , glm::vec3& rayDirection , glm::vec3& boxCenter , glm::vec3& boxMin, glm::vec3& boxMax , std::vector<glm::vec3>& axes , glm::vec3& halfExtents)
	{		
		// Sphere box collision but with a sphere of radius 0
		glm::vec3 closestPointRay;
		PhysicsUtil::MinDistanceSquaredPointRay(boxCenter , rayStartPosition, rayDirection , closestPointRay);

		return SphereBoxCollision(closestPointRay, boxCenter, 0, boxMin, boxMax, axes, halfExtents);
	}

	// Ray capsuale collision detection
	bool RayCapsuleCollision(glm::vec3& startPositionRay, glm::vec3& direction, glm::vec3& A, glm::vec3& B, float capsRadius)
	{
		// We only need to find the minimum distance from the ray and line segment and check that with our capsule radius
		return PhysicsUtil::MinDistanceSquaredLineSegmentRay(A , B , startPositionRay , direction) <= capsRadius * capsRadius;
	}

	// Ray Mesh collision detection
	bool RayMeshCollision()
	{
		return false;
	}
	
	// Line segment ray collision detection
	bool LineSegmentRayCollision(glm::vec3& A , glm::vec3& B, glm::vec3& rayStartPoint, glm::vec3& rayDirection)
	{
		// Hacky solution but it works for the moment MIGHT CHANGE THIS LATER
		// Check if they intersect first (make the longest line segment possible largest value for a float)
		glm::vec3 rayEndPoint = glm::normalize(rayDirection) * std::numeric_limits<float>::infinity();

		// We have an intersection 
		if (PhysicsUtil::MinDistanceSquaredTwoSegments(A, B, rayStartPoint, rayEndPoint) == std::numeric_limits<float>::epsilon()) return 0.0f;
	}

}