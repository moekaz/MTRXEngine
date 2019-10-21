#include <PrecompiledHeader.h>
#include <utils/RaycastUtil.h>

namespace mtrx
{
	namespace RaycastUtil
	{
		bool RaySphereCollision(const glm::vec3& sphereCenter, float sphereRadius, const glm::vec3& startPointRay, const glm::vec3& rayDirection)
		{
			glm::vec3 closestPoint;
			return PhysicsUtil::MinDistanceSquaredPointRay(sphereCenter, startPointRay, rayDirection, closestPoint) <= sphereRadius * sphereRadius;
		}

		bool RayBoxCollision(const glm::vec3& rayStartPosition, const glm::vec3& rayDirection, const glm::vec3& boxCenter, const glm::vec3* axes, const glm::vec3& halfExtents)
		{
			// Sphere box collision but with a sphere of radius 0
			glm::vec3 closestPointRay;
			PhysicsUtil::MinDistanceSquaredPointRay(boxCenter, rayStartPosition, rayDirection, closestPointRay);

			return CollisionUtil::SphereBoxCollision(closestPointRay, boxCenter, 0, axes, halfExtents);
		}

		bool RayCapsuleCollision(const glm::vec3& startPositionRay, const glm::vec3& direction, const glm::vec3& A, const glm::vec3& B, float capsRadius)
		{
			// We only need to find the minimum distance from the ray and line segment and check that with our capsule radius
			return PhysicsUtil::MinDistanceSquaredLineSegmentRay(A, B, startPositionRay, direction) <= capsRadius * capsRadius;
		}

		bool RayMeshCollision()
		{
			return false;
		}

		// TBD: THIS IS NOT CORRECT CHANGE THISSSSSS!!!!
		// Line segment ray collision detection
		bool LineSegmentRayCollision(const glm::vec3& A, const glm::vec3& B, const glm::vec3& rayStartPoint, const glm::vec3& rayDirection)
		{
			// Hacky solution but it works for the moment MIGHT CHANGE THIS LATER
			// Check if they intersect first (make the longest line segment possible largest value for a float)
			glm::vec3 rayEndPoint = glm::normalize(rayDirection) * std::numeric_limits<float>::infinity();

			// Check for an intersection 
			return PhysicsUtil::MinDistanceSquaredTwoSegments(A, B, rayStartPoint, rayEndPoint) == std::numeric_limits<float>::epsilon();
		}

		Collider* RaycastUnfiltered(const std::map<int, Collider*>& colliders, const glm::vec3& rayStartPosition, const glm::vec3& rayDirection)
		{
			Ray ray = Ray(rayStartPosition, rayDirection); // Create a ray in the direction
			std::map<int, Collider*>::const_iterator iter;

			for (iter = colliders.begin(); iter != colliders.end(); ++iter)
			{
				if (iter->second->RaycastCollision(ray))
					return iter->second; // Do the raycast and check for that
			}

			return NULL;
		}

		Collider* RaycastFiltered(const std::map<int, Collider*>& colliders, const std::vector<Collider*>& filterColliders, const glm::vec3& rayStartPosition, const glm::vec3& rayDirection)
		{
			Ray ray = Ray(rayStartPosition, rayDirection);  // Create a ray in the direction
			std::map<int, Collider*> filterCollidersMap;   // Map of the filtered colliders
			std::map<int, Collider*>::const_iterator iter; // Iterator of the collider map

			// Store the vector in a map for quick access (makes filtering much more efficient)
			for (unsigned int i = 0; i < filterColliders.size(); i++)
			{
				filterCollidersMap[filterColliders[i]->GetColliderId()] = filterColliders[i];
			}

			// Go through the colliders checking for raycast collisions after filtering out the ones we don't want
			for (iter = colliders.begin(); iter != colliders.end(); ++iter)
			{
				if (filterCollidersMap.find(iter->first) != filterCollidersMap.end())
					continue; // If it is filtered then skip the collision check
				if (iter->second->RaycastCollision(ray))
					return iter->second; // Do the raycast and check for that
			}

			return NULL;
		}
	}
}