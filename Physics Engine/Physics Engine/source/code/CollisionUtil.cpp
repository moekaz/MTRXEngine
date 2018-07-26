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
		// Check if the sphere's center is inside the box 
		if (center1.x > min.x && center1.x < max.x &&
			center1.y > min.y && center1.y < max.y &&
			center1.z > min.z && center1.z < max.z) return true;
		
		// The sphere is not contained in the box or at least the center is not inside the box
		// Clamp the center to the closest point on the OBB (The same for AABB) then check distance to that box
		glm::vec3 direction = center1 - center2;		// Starting direction
		glm::vec3 closestPoint = center2;

		// For the 3 axes 
		for (int i = 0; i < 3; i++)
		{
			float distance = glm::dot(direction, axes[i]); //direction.DotProduct(axes[i]);

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
		return PhysicsUtil::MinDistanceSquaredPointSegment(A , B , center1 , vec) <= (radius1 + radius2) * (radius1 * radius2);
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

		return SphereBoxCollision(center2, center1, radius, min, max, axes, halfExtents);
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
}