#pragma once

#include <utils/GJKUtil.h>
#include <utils/PhysicsUtil.h>

namespace mtrx
{
	namespace CollisionUtil
	{
		bool SphereSphereCollision(const glm::vec3& center1, const glm::vec3& center2, float radius1, float radius2);
		bool SphereBoxCollision(const glm::vec3& center1, const glm::vec3& center2, float radius, const glm::vec3* axes, const glm::vec3& halfExtents);
		bool SphereCapsuleCollision(const glm::vec3&  center1, const glm::vec3& center2, float radius1, float radius2, const glm::vec3& A, const glm::vec3& B);
		bool SphereMeshCollision();
		bool BoxCapsuleCollision(const glm::vec3& center1, const glm::vec3& center2, const glm::vec3& A, const glm::vec3& B, float radius, const glm::vec3* axes, const glm::vec3& halfExtents);
		bool BoxMeshCollision();
		bool CapsuleCapsuleCollision(const glm::vec3& A1, const glm::vec3& B1, const glm::vec3& A2, const glm::vec3& B2, float radius1, float radius2);
		bool CapsuleMeshCollision();
		bool MeshMeshCollision();

		// Allows us to use any templatable container as long as it has an iterator
		template<typename Iterator,
			typename = std::enable_if_t<std::is_same<glm::vec3*, typename std::iterator_traits<Iterator>::value_type>::value, Iterator>>
		inline bool ConvexShapeCollision(const Iterator& startVertices1, const Iterator& endVertices1, const Iterator& startVertices2, const Iterator& endVertices2)
		{
			return GJKUtil::Collision(startVertices1, endVertices1, startVertices2, endVertices2);
		}

		// Allows us to use any templatable container as long as it has an iterator
		template<typename Iterator,
			typename = std::enable_if_t<std::is_same<glm::vec3*, typename std::iterator_traits<Iterator>::value_type>::value, Iterator>>
		inline bool BoxBoxCollision(const Iterator& startVertices1, const Iterator& endVertices1, const Iterator& startVertices2, const Iterator& endVertices2)
		{
			return ConvexShapeCollision(startVertices1, endVertices1, startVertices2, endVertices2);
		}
	}
}