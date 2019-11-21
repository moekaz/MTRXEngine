#include <PrecompiledHeader.h>
#include <utils/CollisionUtil.h>

namespace mtrx
{
	namespace CollisionUtil
	{
		bool SphereSphereCollision(const glm::vec3& center1, const glm::vec3& center2, float radius1, float radius2)
		{
			glm::vec3 diff = center1 - center2;
			float sumRadii = radius1 + radius2;
			return glm::dot(diff, diff) <= sumRadii * sumRadii;
		}

		bool SphereAABBCollision(const glm::vec3& center, const float radius, const glm::vec3& center1, const float* halfExtents)
		{
			// TBD: Add this to the util file
			// Find the closest pt on the AABB from the sphere center
			glm::vec3 closestPt = center;

			for (int i = 0; i < 3; ++i)
			{
				float min = center1[i] - halfExtents[i];
				float max = center1[i] + halfExtents[i];

				if (closestPt[i] < min)
					closestPt[i] = min;
				else if (closestPt[i] < max)
					closestPt[i] = max;
			}

			glm::vec3 diff = closestPt - center;
			return glm::dot(diff, diff) >= SQR(radius);
		}

		bool SphereOOBBCollision(const glm::vec3& center, const float radius, const glm::vec3& center1, const glm::vec3* axes, const float* halfExtents)
		{
			// Clamp the center to the closest point on the OBB then check distance to that box
			glm::vec3 direction = center - center1;		// Starting direction
			glm::vec3 closestPoint = center1;

			// For the 3 axes 
			for (int i = 0; i < 3; ++i)
			{
				float distance = glm::dot(direction, axes[i]);

				if (distance > halfExtents[i]) 
					distance = halfExtents[i];
				else if (distance < -halfExtents[i]) 
					distance = -halfExtents[i];

				closestPoint += axes[i] * distance;
			}

			// Sphere point collision detection
			glm::vec3 difference = center1 - closestPoint;
			return glm::dot(difference, difference) <= radius * radius;
		}

		bool SphereCapsuleCollision(const glm::vec3& center1, const glm::vec3& center2, float radius1, float radius2, const glm::vec3& A, const glm::vec3& B)
		{
			// If the closest point to the sphere's center is of distance less than the radii of the 2 colliders then we have a collision
			return PhysicsUtil::MinDistanceSquaredPointSegment(A, B, center1).first <= (radius1 + radius2) * (radius1 + radius2);
		}

		bool CapsuleCapsuleCollision(const glm::vec3& A1, const glm::vec3& B1, const glm::vec3& A2, const glm::vec3& B2, float radius1, float radius2)
		{
			// Min distance between the 2 heights is greater than the sum of the radii
			return PhysicsUtil::MinDistanceSquaredTwoSegments(A1, B1, A2, B2) <= (radius1 + radius2) * (radius1 + radius2);
		}

		bool CapsuleAABBCollision(const glm::vec3& A, const glm::vec3& B, const float radii, const glm::vec3& center, const float* halfExtents)
		{
			// This is based on a paper and i am not sure how this exactly works but it seems like its project onto XZ plane
			glm::vec3 min = glm::vec3(center[0] - halfExtents[0], center[1] - halfExtents[1], center[2] - halfExtents[2]);
			glm::vec3 max = glm::vec3(center[0] + halfExtents[0], center[1] + halfExtents[1], center[2] + halfExtents[2]);

			if (A.y < min.y || A.y > max.y)
			{
				float diff = A.x - max.x;
				float diff1 = A.z - max.z;
				if (std::abs(A.x - max.x) < radii || std::abs(A.x - min.x) < radii || std::abs(A.z - max.z) < radii || std::abs(A.z - min.z) < radii)
					return true;
			}
			else
				return SphereAABBCollision(A, radii, center, halfExtents) || SphereAABBCollision(B, radii, center, halfExtents);
		}

		bool AABBCollision(const glm::vec3& center, const float* halfExtents, const glm::vec3& center1, const float* halfExtents1)
		{
			return !abs(center.x - center1.x) > (halfExtents[0] + halfExtents1[0]) &&
				!abs(center.y - center1.y) > (halfExtents[1] + halfExtents1[1]) &&
				!abs(center.z - center1.z) > (halfExtents[2] + halfExtents1[2]);
		}
	}
}