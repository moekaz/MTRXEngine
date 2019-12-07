#pragma once

#define MAX_NUM_ITERATIONS 128	// Helps with better performance for more complicated convex shapes while sacrificing a little on accuracy

#include <Defs.h>
#include <utils/PhysicsUtil.h>

namespace mtrx
{
	/**
	 * @brief Utility class for the implementation of the GJK algorithm used for collision detection between convex shape colliders @see mtrx::ConvexShapeCollider
	 * 
	 * Some resources on the algorithm:
	 * 
	 *	@link https://caseymuratori.com/blog_0003
 	 *	@link http://www.dyn4j.org/2010/04/gjk-gilbert-johnson-keerthi/#gjk-minkowski
 	 *	@link http://vec3.ca/gjk/implementation/
 	 *	@link http://in2gpu.com/2014/05/18/gjk-algorithm-3d/
	 * 
	 */
	class GJKUtil
	{
	public:

		/**
		 * @brief Implementation of GJK Collision detection algorithm @see mtrx::ConvexShapeCollider
		 * 
		 * @tparam Iterator The type of iterator we will use for vertices
		 * @tparam std::enable_if_t<std::is_same<glm::vec3*, typename std::iterator_traits<Iterator>::value_type>::value> Iterator template checks
		 * @tparam Iterator1 The type of iterator we will use for vertices
		 * @tparam std::enable_if_t<std::is_same<glm::vec3*, typename std::iterator_traits<Iterator1>::value_type>::value> Iterator template checks
		 * @param startVertices1 Iterator to the beginning of the first vertex list for first convex shape
		 * @param endVertices1 Iterator to the end of the first vertex list of the first convex shape 
		 * @param startVertices2 Iterator to the beginning of the second vertex list for the second convex shape
		 * @param endVertices2 Iterator to the end of the second vertex list of the second convex shape  
		 * @return true The 2 convex shape colliders collide
		 * @return false The 2 convex shape colliders do not collide
		 */
		template<typename Iterator, typename = std::enable_if_t<std::is_same<glm::vec3*, typename std::iterator_traits<Iterator>::value_type>::value>,
			typename Iterator1, typename = std::enable_if_t<std::is_same<glm::vec3*, typename std::iterator_traits<Iterator1>::value_type>::value>>
		static bool Collision(const Iterator& startVertices1, const Iterator& endVertices1, const Iterator1& startVertices2, const Iterator1& endVertices2) 
		{
			Simplex simplex;
			glm::vec3 searchDirection = glm::vec3(-1, 0, 0);

			simplex.c = Support(startVertices1, endVertices1, startVertices2, endVertices2, searchDirection);
			searchDirection = -simplex.c;
			simplex.b = Support(startVertices1, endVertices1, startVertices2, endVertices2, searchDirection);

			// if the farthest support point is not in the direction of the search direction then we cannot have a collision
			if (glm::dot(simplex.b, searchDirection) < 0)
				return false;

			// Setup a new direction vector
			glm::vec3 BC = simplex.c - simplex.b;
			glm::vec3 BO = -simplex.b;
			searchDirection = PhysicsUtil::TripleCross(BC, BO, BC);

			simplex.size = 2;

			// Simplex GJK logic loop
			for (int i = 0; i < MAX_NUM_ITERATIONS; ++i)
			{
				glm::vec3 a = Support(startVertices1, endVertices1, startVertices2, endVertices2, searchDirection); // Get the next point
				if (glm::dot(a, searchDirection) < 0)	// We cannot have a collision
					return false;
				else if (UpdateSimplex(simplex, searchDirection, a))	// Update the simplex and set a new direction vector
					return true;
			}

			// Degenerate simplex we are probably colliding
			MTRX_WARN("GJK algo has generated a degenerate simplex");
			return true;
		}

	private:
		
		// Update the values of the simplex after adding points from support

		/**
		 * @brief Update the simplex values or return a collision
		 * 
		 * @param simplex The simplex generated to be modified according the the new vertices
		 * @param direction The direction that we will be finding points using
		 * @param a The newest point to be added to the simplex
		 * @return true The simplex encapsulates the origin and thus there exists a collision
		 * @return false The simplex does not encapsule the origin and thus modified the simplex to continue search
		 */
		static bool UpdateSimplex(Simplex& simplex, glm::vec3& direction, glm::vec3& a);
		// Update the values of the simplex when we have a triangle simplex
		
		/**
		 * @brief Updating the simplex values from a triangle simplex
		 * 
		 * @param simplex The simplex we want to update
		 * @param direction The direction for the search 
		 * @param a The new vector that we got from the support function @see mtrx::GJKUtil::Support
		 * @return true N/A as a triangle simplex cannot encapsulate a point in 3d space
		 * @return false Always returned
		 */
		static bool TriangleSimplexUpdate(Simplex& simplex, glm::vec3& direction, glm::vec3& a);
		// Update the values of the simplex when we have a tetraheadron simplex
		
		/**
		 * @brief Update the simplex based upon a tetrahedron simplex
		 * 
		 * @param simplex The simplex we want to update
		 * @param direction The direction that we are searching with
		 * @param a The new vertex generated from the support function @see mtrx::GJKUtil::Support
		 * @return true The tetrahedron encapsulate the origin signifying a collision
		 * @return false The tetrahedron does not encapsulate the origin and thus the simplex needs to be modified or recalculated
		 */
		static bool TetrahedronSimplexUpdate(Simplex& simplex, glm::vec3& direction, glm::vec3& a);
		// Extra checks for tetrahedron simplexes

		/**
		 * @brief Utility function for updating tetrahedron simplex knowing that there is no collision
		 * 
		 * @param simplex The simplex that we want to modify
		 * @param AO Line of the triangle 'AO'
		 * @param AB Line of the triangle 'AB'
		 * @param AC Line of the triangle 'AC'
		 * @param ABC normal of the the plane ABC of the triangle
		 * @param direction The direction vector of the search
		 * @param a The new vector from the support functionality @see mtrx::GJKUtil::Support
		 */
		static void TetrahedronChecks(Simplex& simplex, glm::vec3& AO, glm::vec3& AB, glm::vec3& AC, glm::vec3& ABC, glm::vec3& direction, glm::vec3& a);
		
		// Support functionality for convex shape collider vertices
		
		/**
		 * @brief Support functionality for convex shape collider gives us a point in Minkowski space
		 * that is closest to the direction vector given
		 * 
		 * @tparam Iterator The type of iterator we will use for vertices
		 * @tparam std::enable_if_t<std::is_same<glm::vec3*, typename std::iterator_traits<Iterator>::value_type>::value> Iterator template checks
		 * @tparam Iterator1 The type of iterator we will use for vertices
		 * @tparam std::enable_if_t<std::is_same<glm::vec3*, typename std::iterator_traits<Iterator1>::value_type>::value> Iterator template checks
		 * @param startVertices1 Iterator to the beginning of the first vertex list for first convex shape
		 * @param endVertices1 Iterator to the end of the first vertex list of the first convex shape 
		 * @param startVertices2 Iterator to the beginning of the second vertex list for the second convex shape
		 * @param endVertices2 Iterator to the end of the second vertex list of the second convex shape  
		 * @param direction The direction that we want to find a vertex in the direction of
		 * @return glm::vec3 A vertex in minkowski space in the direction given to be added to the simplex
		 */
		template<typename Iterator, typename = std::enable_if_t<std::is_same<glm::vec3*, typename std::iterator_traits<Iterator>::value_type>::value>,
			typename Iterator1, typename = std::enable_if_t<std::is_same<glm::vec3*, typename std::iterator_traits<Iterator1>::value_type>::value>>
		static glm::vec3 Support(const Iterator& startVertices1, const Iterator& endVertices1, const Iterator1& startVertices2, const Iterator1& endVertices2, const glm::vec3& direction)
		{
			const glm::vec3* p1 = FarthestPointInDirection(startVertices1, endVertices1, direction);
			const glm::vec3* p2 = FarthestPointInDirection(startVertices2, endVertices2, -direction);
			return *p1 - *p2;
		}

		
		// Return farthest point with respect to a certain direction

		/**
		 * @brief Get a point in the vertex list that is closest (direction-wise) to the 
		 * direction vector
		 * 
		 * @tparam Iterator The type of iterator we will use for vertices
		 * @tparam std::enable_if_t<std::is_same<glm::vec3*, typename std::iterator_traits<Iterator>::value_type>::value> Iterator template checks
		 * @param startVertices Iterator to the beginning of the vertex list  
		 * @param endVertices Iterator to the end of the vertex list
		 * @param direction The direction vector used to find the farthest point
		 * @return glm::vec3* The farthest point with the give direction
		 */
		template<typename Iterator, typename = std::enable_if_t<std::is_same<glm::vec3*, typename std::iterator_traits<Iterator>::value_type>::value>>
		static glm::vec3* FarthestPointInDirection(const Iterator& startVertices, const Iterator& endVertices, const glm::vec3& direction)
		{
			float maxDot = -std::numeric_limits<float>::infinity();
			glm::vec3* farthest = nullptr;

			for (auto iter = startVertices; iter != endVertices; ++iter)
			{
				glm::vec3* currentVertex = *iter;
				float dot = glm::dot(*currentVertex, direction);
				if (dot > maxDot)
				{
					maxDot = dot;
					farthest = currentVertex;
				}
			}

			// Check that we have a vertex to use
			assert(farthest);
 			return farthest;
		}
	};
}