#include <PrecompiledHeader.h>
#include <utils/CollisionUtil.h>

namespace mtrx
{
	namespace CollisionUtil
	{
		// Sphere sphere collision detection
		bool SphereSphereCollision(const glm::vec3& center1, const glm::vec3& center2, float radius1, float radius2)
		{
			glm::vec3 diff = center1 - center2;
			float sumRadii = radius1 + radius2;
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
	}
}