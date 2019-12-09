#pragma once

#include <math/Ray.h>
#include <Defs.h>

namespace mtrx
{
	/**
	 * @brief Utility namespace for some basic calculations that are useful for collision detection and other physics related functionality
	 * 
	 */
	namespace PhysicsUtil
	{
		/**
		 * @brief Implementation of triple cross product
		 * 
		 * @param a First vector
		 * @param b Second vector
		 * @param c Third vector
		 * @return glm::vec3 The result of the triple cross product
		 */
		glm::vec3 TripleCross(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c);
		
		/**
		 * @brief Minimum distance squared between 2 infinite line. The square of the minimum distance is used for optimization purposes
		 * 
		 * @param A Point on first line
		 * @param B Point on first line
		 * @param C Point on second line
		 * @param D Point on second line
		 * @return float The minimum distance squared between the 2 infinite lines
		 */
		float MinDistanceTwoLines(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C, const glm::vec3& D);

		/**
		 * @brief Minimum distance squared between 2 line segments. The square of the minimum distance is used for optimization purposes
		 * @link http://geomalgorithms.com/a07-_distance.html#dist3D_Segment_to_Segment
		 * 
		 * @param A First end of the line segment
		 * @param B Second end of the line segment
		 * @param C First end of the second line segment
		 * @param D Second end of the second line segment
		 * @return float The minimum distance squared between 2 line segments
		 */
		float MinDistanceSquaredTwoSegments(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C, const glm::vec3& D);
		
		/**
		 * @brief Minimum distance squared of a point and ray. The square of the minimum distance is used for optimization purposes
		 * 
		 * @param point A point in 3d space we want to check the distance for
		 * @param startPointRay Start point of the ray
		 * @param rayDirection The normalized direction of the ray
		 * @return std::pair<float, glm::vec3> The minimum distance squared and the closest point
		 */
		std::pair<float, glm::vec3> MinDistanceSquaredPointRay(const glm::vec3& point, const glm::vec3& startPointRay, const glm::vec3& rayDirection);
		
		/**
		 * @brief Minimum distance squared of a point and a line segment. The square of the minimum distance is used for optimization purposes
		 * 
		 * @param A The point we want to check the distance for
		 * @param B The first end point of the line segment
		 * @param C The second end point of the line segment
		 * @return std::pair<float, glm::vec3> The minimum distance squared and the closest point
		 */
		std::pair<float, glm::vec3> MinDistanceSquaredPointSegment(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C);
		
		/**
		 * @brief Minimum distance squared Line segment and ray. Can be broken down into a line segment minimum distance squared @see mtrx::PhysicsUtil::MinimumDistanceSquaredTwoSegments
		 * The square of the minimum distance is used for optimization purposes
		 * 
		 * @param a The first end point of the line segment
		 * @param b The second end point of the line segment
		 * @param rayStart The starting point of the ray 
		 * @param rayDirection The normalized direction of the ray
		 * @return float The minimum distance squared of the line segment and the ray
		 */
		float MinDistanceSquaredLineSegmentRay(const glm::vec3& a, const glm::vec3& b, const glm::vec3& rayStart, const glm::vec3& rayDirection);
		
		/**
		 * @brief Minimum distance squared between a point and triangle. The square of the minimum distance is used for optimization purposes
		 * 
		 * @param pt The point we want to check the distance for
		 * @param a The first point of the triangle
		 * @param b The second point of the triangle
		 * @param c The third point of the triangle
		 * @return float The minimum distance squared 
		 */
		float MinDistanceSquaredPointTriangle(const glm::vec3& pt, const glm::vec3& a, const glm::vec3& b, const glm::vec3& c);
		
		/**
		 * @brief Minimum distance squared of line segment and triangle. The square of the minimum distance is used for optimization purposes
		 * 
		 * @param a The first end point of the line segment
		 * @param b The second end point of the line segment
		 * @param c First point of the triangle
		 * @param d Second point of the triangle
		 * @param e Third point of the triangle
		 * @return float The minimum distance squared between the line segment and the triangle
		 */
		float MinDistanceSquaredLineSegmentTriangle(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, const glm::vec3& d, const glm::vec3& e);
		
		/**
		 * @brief Minimum distance squared between a point and an AABB. The square of the minimum distance is used for optimization purposes
		 * 
		 * @param pt The point we want to check the distance for
		 * @param center The center of the AABB collider @see mtrx::AABBCollider
		 * @param halfExtents The half extents of the AABBCollider @see mtrx::AABBCollider
		 * @return std::pair<float, glm::vec3> The minimum distance squared and the closest point
		 */
		std::pair<float, glm::vec3> MinDistanceSquaredPointAABB(const glm::vec3& pt, const glm::vec3& center, const float* halfExtents);

		/**
		 * @brief Implementation of Slerp which is a lerp for rotations 
		 * 
		 * @param firstRotation start position of the rotation
		 * @param secondRotation End position of the rotation
		 * @param t parameter between [0, 1] to interpolate between the 2 rotations
		 * @return glm::quat The rotation interpolated between the 2 rotations
		 */
		glm::quat Slerp(const glm::quat& firstRotation, const glm::quat& secondRotation, float t);
		
		/**
		 * @brief Implementation of linear interpolation 
		 * 
		 * @param startingPosition Start position 
		 * @param destination End position
		 * @param t Parameter between [0, 1] 
		 * @return glm::vec3 A vector between the 2 vectors influenced by the t value
		 */
		glm::vec3 Lerp(const glm::vec3& startingPosition, const glm::vec3& destination, float t);
		
		/**
		 * @brief Easing function for the t parameter to be used for lerping functions.
		 * The easing function is a half sin curve that allows for a slow start and a slow end 
		 * 
		 * @param t Parameter between [0, 1]
		 * @return float New t value according to the easing function
		 */
		float Ease(float t);

		/**
		 * @brief Triangulating a convex shape by fan triangulation which is using the first vertex as a starting point 
		 * for all triangules and fanning out to the other vertices 
		 * 
		 * @tparam Iterator Iterator type that is used by the collection of vertices
		 * @tparam std::enable_if_t<std::is_same<glm::vec3*, typename std::iterator_traits<Iterator>::value_type>::value> Iterator template check
		 * @param startVertices Iterator to the beginning of the vertex list
		 * @param endVertices Iterator to the end of the vertex list
		 * @param size The size of the vertex list
		 * @return std::vector<Triangle> A vector of triangles representing the triangulated mesh
		 */
		template<typename Iterator, typename = std::enable_if_t<std::is_same<glm::vec3*, typename std::iterator_traits<Iterator>::value_type>::value>>
		std::vector<Triangle> TriangulateConvexShape(const Iterator& startVertices, const Iterator& endVertices, const int size)
		{
			if (size <= 2) // If we have 2 pts or less
				return {};

			std::vector<Triangle> triangles(size - 2); // We know that it will be of size n - 2		
			for (auto iter = startVertices + 1; iter != endVertices - 1; ++iter)
			{
				triangles.emplace_back(*startVertices , *iter, *(std::next(iter)));
			}

			return triangles;
		}
	}
}