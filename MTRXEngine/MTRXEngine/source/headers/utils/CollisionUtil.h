#pragma once

#include <utils/GJKUtil.h>
#include <utils/PhysicsUtil.h>

namespace mtrx
{
	/**
	 * @brief Namespace used to define some collision detection algorithms that are used to check for collision between different colliders. 
	 * None of these functions require colliders themselves, They use mostly 
	 * primitive classes instead.
	 * 
	 */
	namespace CollisionUtil
	{
		/**
		 * @brief Sphere Sphere collision detection algorithm
		 * 
		 * @param center1 Center of the first sphere collider
		 * @param center2 Center of the second sphere collider
		 * @param radius1 Radius of the first sphere collider
		 * @param radius2 Radius of the second sphere collider
		 * @return true The 2 sphere colliders collide
		 * @return false The 2 sphere colliders do not collide
		 */
		bool SphereSphereCollision(const glm::vec3& center1, const glm::vec3& center2, float radius1, float radius2);

		/**
		 * @brief Sphere Capsule collision detection algorithm
		 * 
		 * @param center1 Center of the sphere collider
		 * @param center2 Center of the capsule collider
		 * @param radius1 Radius of the sphere collider
		 * @param radius2 Radius of the capsule collider
		 * @param A Topmost sphere center for capsule collider
		 * @param B Bottommost sphere center for capsule collider
		 * @return true The sphere and capsule colliders collide
		 * @return false The sphere and capsule colliders do not collide
		 */
		bool SphereCapsuleCollision(const glm::vec3&  center1, const glm::vec3& center2, float radius1, float radius2, const glm::vec3& A, const glm::vec3& B);
		
		/**
		 * @brief Sphere AABB collider collision detection algorithm
		 * 
		 * @param center Center of the sphere collider
		 * @param radius Radius of the sphere collider
		 * @param center1 Center of the AABB collider
		 * @param halfExtents Half Extents of the AABB collider
		 * @return true The sphere and AABB colliders collide
		 * @return false The sphere and AABB colliders do not collide
		 */
		bool SphereAABBCollision(const glm::vec3& center, const float radius, const glm::vec3& center1, const float* halfExtents);

		/**
		 * @brief Sphere OOBB collider collision detection algorithm
		 * 
		 * @param center Center of the sphere collider
		 * @param radius Radius of the sphere collider
		 * @param center1 Center of the OOBB collider
		 * @param axes Axes that define the OOBB world 
		 * @param halfExtents Half extent values of OOBB colliders
		 * @return true Sphere and OOBB colliders collide
		 * @return false Sphere and OOBB colliders do not collide
		 */
		bool SphereOOBBCollision(const glm::vec3& center, const float radius, const glm::vec3& center1, const glm::vec3* axes, const float* halfExtents);
		
		/**
		 * @brief Capsule Capsule collision detection algorithm
		 * 
		 * @param A1 Center of topmost sphere for first capsule
		 * @param B1 Center of bottommost sphere for first capsule
		 * @param A2 Center of topmost sphere for second capsule
		 * @param B2 Center of bottommost sphere for second capsule
		 * @param radius1 Radius of first capsule
		 * @param radius2 Radius of second capsule
		 * @return true Capsule colliders collide
		 * @return false Capsule colliders do not collide
		 */
		bool CapsuleCapsuleCollision(const glm::vec3& A1, const glm::vec3& B1, const glm::vec3& A2, const glm::vec3& B2, float radius1, float radius2);
		
		/**
		 * @brief Capsule AABB collision detection algorithm
		 * 
		 * @param A Center of the topmost sphere for capsule
		 * @param B Center of the bottommost sphere for capsule
		 * @param radii Radii of the capsule
		 * @param center Center of the AABB collider
		 * @param halfExtents Half extents of the AABB collider 
		 * @return true The capsule and AABB colliders collide
		 * @return false The capsule and AABB colliders do not collide
		 */
		bool CapsuleAABBCollision(const glm::vec3& A, const glm::vec3& B, const float radii, const glm::vec3& center, const float* halfExtents);

		/**
		 * @brief AABB AABB collision detection algorithm
		 * 
		 * @param center Center of the first AABB collider
		 * @param halfExtents Half extents of the first AABB collider
		 * @param center1 Center of the second AABB collider
		 * @param halfExtents1 Half extents of the second AABB collider
		 * @return true The AABB colliders collide
		 * @return false The AABB colliders do not collide
		 */
		bool AABBCollision(const glm::vec3& center, const float* halfExtents, const glm::vec3& center1, const float* halfExtents1);

		/**
		 * @brief Convex Shape collision detection algorithm. 
		 * Uses GJK collision detection algorithm @see mtrx::GJKUtil
		 * 
		 * @tparam Iterator An iterator type for the data structure that holds the vertices 
		 * @tparam std::enable_if_t<std::is_same<glm::vec3*, typename std::iterator_traits<Iterator>::value_type>::value> Template parameter check 
		 * @tparam Iterator1 An iterator type for the data structure that holds the vertices 
		 * @tparam std::enable_if_t<std::is_same<glm::vec3*, typename std::iterator_traits<Iterator1>::value_type>::value> Template parameter check 
		 * @param startVertices1 Iterator to the beginning of the vertex list for first convex collider
		 * @param endVertices1 Iterator to the end of the vertex list for first convex collider
		 * @param startVertices2 Iterator to the beginning of the vertex list for the second convex shape collider
		 * @param endVertices2 Iterator to the end of the vertex list for the second convex shape collider
		 * @return true The convex shape colliders collide
		 * @return false The convex shape colliders do not collide
		 */
		template<typename Iterator, typename = std::enable_if_t<std::is_same<glm::vec3*, typename std::iterator_traits<Iterator>::value_type>::value>,
			typename Iterator1, typename = std::enable_if_t<std::is_same<glm::vec3*, typename std::iterator_traits<Iterator1>::value_type>::value>>
		bool ConvexShapeCollision(const Iterator& startVertices1, const Iterator& endVertices1, const Iterator1& startVertices2, const Iterator1& endVertices2)
		{
			return GJKUtil::Collision(startVertices1, endVertices1, startVertices2, endVertices2);
		}

		/**
		 * @brief Convex Shape Capsule collision detection algorithm
		 * 
		 * @tparam Iterator An iterator type for the data structure that holds the vertices 
		 * @tparam std::enable_if_t<std::is_same<glm::vec3*, typename std::iterator_traits<Iterator>::value_type>::value> Template parameter check 
		 * @param startVertices Iterator to the beginning of the vertex list
		 * @param endVertices Iterator to the end of the vertex list
		 * @param size Number of vertices
		 * @param A Center of the topmost sphere in the capsule collider
		 * @param B Center of the bottommost sphere in the capsule collider
		 * @param radii Radii of the capsule collider
		 * @return true The convex shape and capsule colliders collide
		 * @return false The convex shape and capsule colliders collide
		 */
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

		/**
		 * @brief Capsule OOBB Collision detection algorithm
		 * 
		 * @tparam Iterator An iterator type for the data structure that holds the vertices 
		 * @tparam std::enable_if_t<std::is_same<glm::vec3*, typename std::iterator_traits<Iterator>::value_type>::value> Template parameter check 
		 * @param A Center of topmost sphere of capsule collider
		 * @param B Center of bottommost sphere of capsule collider
		 * @param radii Radii of the capsule collider
		 * @param startVertices Iterator to the beginning of the vertices list
		 * @param endVertices Iterator to the end of the vertices list
		 * @param size Number of vertices
		 * @return true The capsule and OOBB colliders collide
		 * @return false The capsule and OOBB colliders do not collide
		 */
		template<typename Iterator, typename = std::enable_if_t<std::is_same<glm::vec3*, typename std::iterator_traits<Iterator>::value_type>::value>>
		bool CapsuleOOBBCollision(const glm::vec3& A, const glm::vec3& B, float radii, const Iterator& startVertices, const Iterator& endVertices, const int size)
		{
			return ConvexShapeCapsuleCollision(startVertices, endVertices, size, A, B, radii);
		}

		/**
		 * @brief AABB and OOBB collision detection algorithm @see mtrx::CollisionUtil::ConvexShapeCollision
		 * 
		 * @tparam Iterator An iterator type for the data structure that holds the vertices 
		 * @tparam std::enable_if_t<std::is_same<glm::vec3*, typename std::iterator_traits<Iterator>::value_type>::value> Template parameter check 
		 * @tparam Iterator1 An iterator type for the data structure that holds the vertices 
		 * @tparam std::enable_if_t<std::is_same<glm::vec3*, typename std::iterator_traits<Iterator1>::value_type>::value> Template parameter check 
		 * @param startVertices1 Iterator to the beginning of the vertex list of the AABB
		 * @param endVertices1 Iterator to the end of the vertex list of the AABB
		 * @param startVertices2 Iterator to the beginning of the vertex list of the OOBB 
		 * @param endVertices2 Iterator to the end of the vertex list of the OOBB
		 * @return true The AABB and OOBB colliders collide
		 * @return false The AABB and OOBB colliders do not collide
		 */
		template<typename Iterator, typename = std::enable_if_t<std::is_same<glm::vec3*, typename std::iterator_traits<Iterator>::value_type>::value>,
			typename Iterator1, typename = std::enable_if_t<std::is_same<glm::vec3*, typename std::iterator_traits<Iterator1>::value_type>::value>>
		bool AABBOOBBCollision(const Iterator& startVertices1, const Iterator& endVertices1, const Iterator1& startVertices2, const Iterator1& endVertices2)
		{
			return ConvexShapeCollision(startVertices1, endVertices1, startVertices2, endVertices2);
		}

		/**
		 * @brief OOBB and OOBB collision detection algorithm @see mtrx::CollisionUtil::ConvexShapeCollision
		 * 
		 * @tparam Iterator An iterator type for the data structure that holds the vertices 
		 * @tparam std::enable_if_t<std::is_same<glm::vec3*, typename std::iterator_traits<Iterator>::value_type>::value> Template parameter check 
		 * @tparam Iterator1 An iterator type for the data structure that holds the vertices 
		 * @tparam std::enable_if_t<std::is_same<glm::vec3*, typename std::iterator_traits<Iterator1>::value_type>::value> Template parameter check 
		 * @param startVertices1 Iterator to the beginning of the vertex list of the first OOBB 
		 * @param endVertices1 Iterator to the end of the vertex list of the first OOBB
		 * @param startVertices2 Iterator to the beginning of the vertex list of the second OOBB
		 * @param endVertices2 Iterator to the end of the vertex list of the second OOBB
		 * @return true The OOBB colliders collide
		 * @return false The OOBB colliders do not collide
		 */
		template<typename Iterator, typename = std::enable_if_t<std::is_same<glm::vec3*, typename std::iterator_traits<Iterator>::value_type>::value>,
			typename Iterator1, typename = std::enable_if_t<std::is_same<glm::vec3*, typename std::iterator_traits<Iterator1>::value_type>::value>>
		bool OOBBCollision(const Iterator& startVertices1, const Iterator& endVertices1, const Iterator1& startVertices2, const Iterator1& endVertices2)
		{
			return ConvexShapeCollision(startVertices1, endVertices1, startVertices2, endVertices2);
		}

		/**
		 * @brief Convex Shape Sphere collision detection algorithm
		 * 
		 * @tparam Iterator An iterator type for the data structure that holds the vertices 
		 * @tparam std::enable_if_t<std::is_same<glm::vec3*, typename std::iterator_traits<Iterator>::value_type>::value> Template parameter check 
		 * @param startVertices Iterator to the beginning of the vertex list of the convex shape 
		 * @param endVertices Iterator to the end of the vertex list of the convex shape 
		 * @param size Number of vertices of convex shape collider
		 * @param center Center of the sphere collider
		 * @param radius Radius of the sphere collider
		 * @return true The convex shape and sphere colliders collide
		 * @return false The convex shape and sphere colliders do not collide
		 */
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