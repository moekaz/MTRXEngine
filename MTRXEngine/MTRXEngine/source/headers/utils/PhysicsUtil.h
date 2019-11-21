#pragma once

#include <math/Ray.h>
#include <utils/CollisionUtil.h>
#include <utils/RaycastCollisionUtil.h>
#include <colliders/Collider.h>

namespace mtrx
{
	namespace PhysicsUtil
	{
		glm::vec3 TripleCross(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c);
		
		float MinDistanceTwoLines(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C, const glm::vec3& D);
		
		// TBD: LOOK AT IMPLEMENTATION IN CHRISTER ERICSON'S BOOK
		float MinDistanceSquaredTwoSegments(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C, const glm::vec3& D);


		std::pair<float, glm::vec3> MinDistanceSquaredPointRay(const glm::vec3& point, const glm::vec3& startPointRay, const glm::vec3& rayDirection);
		std::pair<float, glm::vec3> MinDistanceSquaredPointSegment(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C);
		float MinDistanceSquaredLineSegmentRay(const glm::vec3& a, const glm::vec3& b, const glm::vec3& rayStart, const glm::vec3& rayDirection);
		float MinDistanceSquaredPointTriangle(const glm::vec3& pt, const glm::vec3& a, const glm::vec3& b, const glm::vec3& c);
		
		
		//TBD: Look at Christer Ericson's book for more information on this
		float MinDistanceSquaredLineSegmentTriangle(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, glm::vec3& d, glm::vec3& e);

		glm::quat Slerp(const glm::quat& firstRotation, const glm::quat& secondRotation, float t);
		glm::vec3 Lerp(const glm::vec3& startingPosition, const glm::vec3& destination, float t);
		float Ease(float t);

		// Triangulate using fan triangulation
		template<typename Iterator, typename = std::enable_if_t<std::is_same<glm::vec3*, typename std::iterator_traits<Iterator>::value_type>::value>,
			typename Iterator1, typename = std::enable_if_t<std::is_same<glm::vec3*, typename std::iterator_traits<Iterator1>::value_type>::value>>
		std::vector<Triangle> TriangulateConvexShape(const Iterator& startVertices, const Iterator& endVertices, const int size)
		{
			if (size <= 2) // If we have 2 pts or less
				return {};

			std::vector<Triangle> triangles(size - 2); // We knw that it will be of size n - 2		
			for (auto iter = startVertices + 1; iter != endVertices - 1; ++iter)
			{
				triangles.push_back({ startVertices , *iter, *(std::next(iter)) });
			}

			return triangles;
		}
	}
}