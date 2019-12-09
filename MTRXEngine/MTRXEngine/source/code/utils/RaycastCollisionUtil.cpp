#include <PrecompiledHeader.h>
#include <utils/RaycastCollisionUtil.h>

namespace mtrx
{
	namespace RaycastCollisionUtil
	{
		bool RaySphereCollision(const glm::vec3& sphereCenter, float sphereRadius, const glm::vec3& startPointRay, const glm::vec3& rayDirection)
		{
			return PhysicsUtil::MinDistanceSquaredPointRay(sphereCenter, startPointRay, rayDirection).first <= sphereRadius * sphereRadius;
		}

		bool RayAABBCollision(const glm::vec3& rayStart, const glm::vec3& rayDirection, const glm::vec3& center, const glm::vec3* axes, const float* halfExtents)
		{
			glm::vec3 min = glm::vec3(center[0] - ((*axes)[0] * halfExtents[0]), center[1] - ((*axes)[1] * halfExtents[1]), center[2] - ((*axes)[2] * halfExtents[2]));
			glm::vec3 max = glm::vec3(center[0] + ((*axes)[0] * halfExtents[0]), center[1] + ((*axes)[1] * halfExtents[1]), center[2] + ((*axes)[2] * halfExtents[2]));

			float t[8];
			t[0] = (min.x - rayStart.x) / rayDirection.x;
			t[1] = (max.x - rayStart.x) / rayDirection.x;
			t[2] = (min.y - rayStart.y) / rayDirection.y;
			t[3] = (max.y - rayStart.y) / rayDirection.y;
			t[4] = (min.z - rayStart.z) / rayDirection.z;
			t[5] = (max.z - rayStart.z) / rayDirection.z;
			t[6] = std::max(std::max(std::min(t[0], t[1]), std::min(t[2], t[3])), std::min(t[4], t[5]));
			t[7] = std::min(std::min(std::max(t[0], t[1]), std::max(t[2], t[3])), std::max(t[4], t[5]));
			
			return !(t[7] < 0 || t[6] > t[7]);

			//return t[8];
		}

		bool RayCapsuleCollision(const glm::vec3& startPositionRay, const glm::vec3& direction, const glm::vec3& A, const glm::vec3& B, float capsRadius)
		{
			// We only need to find the minimum distance from the ray and line segment and check that with our capsule radius
			return PhysicsUtil::MinDistanceSquaredLineSegmentRay(A, B, startPositionRay, direction) <= SQR(capsRadius);
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