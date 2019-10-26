#include <PrecompiledHeader.h>
#include <utils/RaycastCollisionUtil.h>

namespace mtrx
{
	namespace RaycastCollisionUtil
	{
		bool RaySphereCollision(const glm::vec3& sphereCenter, float sphereRadius, const glm::vec3& startPointRay, const glm::vec3& rayDirection)
		{
			glm::vec3 closestPoint;
			return PhysicsUtil::MinDistanceSquaredPointRay(sphereCenter, startPointRay, rayDirection, closestPoint) <= sphereRadius * sphereRadius;
		}

		bool RayBoxCollision(const glm::vec3& rayStartPosition, const glm::vec3& rayDirection, const glm::vec3& boxCenter, const glm::vec3* axes, const float* halfExtents)
		{
			// Sphere box collision but with a sphere of radius 0
			glm::vec3 closestPointRay;
			PhysicsUtil::MinDistanceSquaredPointRay(boxCenter, rayStartPosition, rayDirection, closestPointRay);

			return CollisionUtil::SphereBoxCollision(closestPointRay, boxCenter, 0.f, axes, halfExtents);
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

		bool LineSegmentRayCollision(const glm::vec3& A, const glm::vec3& B, const glm::vec3& rayStartPoint, const glm::vec3& rayDirection)
		{
			// TBD: Find a better solution for actual ray segment collision detection
			glm::vec3 diff = A - rayStartPoint;
			glm::vec3 ba = A - B;

			float val = ba.y * rayDirection.x - ba.x * rayDirection.y;
			if (val <= std::numeric_limits<float>::epsilon())
				return false;

			float t2 = (diff.y * rayDirection.x - diff.x * rayDirection.y) / val;
			if (t2 < 0 || t2 > 1)
				return false;

			float t1 = 0;
			if (t1 < 0)
				return false;

			return true;
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

			return nullptr;
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

			return nullptr;
		}
	}
}