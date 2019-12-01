#pragma once

#include <utils/GJKUtil.h>
#include <utils/PhysicsUtil.h>

namespace mtrx
{
	namespace CollisionUtil
	{
		bool SphereSphereCollision(const glm::vec3& center1, const glm::vec3& center2, float radius1, float radius2);
		bool SphereCapsuleCollision(const glm::vec3&  center1, const glm::vec3& center2, float radius1, float radius2, const glm::vec3& A, const glm::vec3& B);
		bool SphereAABBCollision(const glm::vec3& center, const float radius, const glm::vec3& center1, const float* halfExtents);
		bool SphereOOBBCollision(const glm::vec3& center, const float radius, const glm::vec3& center1, const glm::vec3* axes, const float* halfExtents);
		bool CapsuleCapsuleCollision(const glm::vec3& A1, const glm::vec3& B1, const glm::vec3& A2, const glm::vec3& B2, float radius1, float radius2);
		bool CapsuleAABBCollision(const glm::vec3& A, const glm::vec3& B, const float radii, const glm::vec3& center, const float* halfExtents);
		bool AABBCollision(const glm::vec3& center, const float* halfExtents, const glm::vec3& center1, const float* halfExtents1);

		// Allows us to use any templatable container as long as it has an iterator
		template<typename Iterator, typename = std::enable_if_t<std::is_same<glm::vec3*, typename std::iterator_traits<Iterator>::value_type>::value>,
			typename Iterator1, typename = std::enable_if_t<std::is_same<glm::vec3*, typename std::iterator_traits<Iterator1>::value_type>::value>>
		bool ConvexShapeCollision(const Iterator& startVertices1, const Iterator& endVertices1, const Iterator1& startVertices2, const Iterator1& endVertices2)
		{
			return GJKUtil::Collision(startVertices1, endVertices1, startVertices2, endVertices2);
		}

		// Allows us to use any templatable container as long as it has an iterator
		template<typename Iterator, typename = std::enable_if_t<std::is_same<glm::vec3*, typename std::iterator_traits<Iterator>::value_type>::value>>
		bool ConvexShapeCapsuleCollision(const Iterator& startVertices, const Iterator& endVertices, const int size, const glm::vec3& A, const glm::vec3& B, const float radii)
		{
			std::vector<Triangle> triangles = PhysicsUtil::TriangulateConvexShape(startVertices, endVertices, size);
			float radiusSqr = SQR(radii);
			for (auto iter = triangles.begin(); iter != triangles.end(); ++iter)
			{
				// Get the minimum distance between each line segment
				if (PhysicsUtil::MinDistanceSquaredLineSegmentTriangle(A, B, *iter->a, *iter->b, *iter->c) <= radiusSqr)
					return true;
			}

			return false;
		}

		template<typename Iterator, typename = std::enable_if_t<std::is_same<glm::vec3*, typename std::iterator_traits<Iterator>::value_type>::value>>
		bool CapsuleOOBBCollision(const glm::vec3& A, const glm::vec3& B, float radii, const Iterator& startVertices, const Iterator& endVertices, const int size)
		{
			return ConvexShapeCapsuleCollision(startVertices, endVertices, size, A, B, radii);
		}

		// Allows us to use any templatable container as long as it has an iterator
		template<typename Iterator, typename = std::enable_if_t<std::is_same<glm::vec3*, typename std::iterator_traits<Iterator>::value_type>::value>,
			typename Iterator1, typename = std::enable_if_t<std::is_same<glm::vec3*, typename std::iterator_traits<Iterator1>::value_type>::value>>
		bool AABBOOBBCollision(const Iterator& startVertices1, const Iterator& endVertices1, const Iterator1& startVertices2, const Iterator1& endVertices2)
		{
			return ConvexShapeCollision(startVertices1, endVertices1, startVertices2, endVertices2);
		}

		// Allows us to use any templatable container as long as it has an iterator
		template<typename Iterator, typename = std::enable_if_t<std::is_same<glm::vec3*, typename std::iterator_traits<Iterator>::value_type>::value>,
			typename Iterator1, typename = std::enable_if_t<std::is_same<glm::vec3*, typename std::iterator_traits<Iterator1>::value_type>::value>>
		bool OOBBCollision(const Iterator& startVertices1, const Iterator& endVertices1, const Iterator1& startVertices2, const Iterator1& endVertices2)
		{
			return ConvexShapeCollision(startVertices1, endVertices1, startVertices2, endVertices2);
		}

		// Allows us to use any templatable container as long as it has an iterator
		template<typename Iterator, typename = std::enable_if_t<std::is_same<glm::vec3*, typename std::iterator_traits<Iterator>::value_type>::value>>
		bool ConvexShapeSphereCollision(const Iterator& startVertices, const Iterator& endVertices, const int size, const glm::vec3& center, const float radius)
		{
			std::vector<Triangle> triangles = PhysicsUtil::TriangulateConvexShape(startVertices, endVertices, size);
			float radiusSqr = SQR(radius);
			for (auto iter = triangles.begin(); iter != triangles.end(); ++iter)
			{
				// Get the distance from each of the triangles 
				if (PhysicsUtil::MinDistanceSquaredPointTriangle(center, *iter->a, *iter->b, *iter->c) <= radiusSqr)
					return true;
			}

			return false;
		}
	}
}