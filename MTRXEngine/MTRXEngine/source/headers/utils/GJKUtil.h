/**
 * 	Author: Mohamed Kazma
 *  Description: Gilbert–Johnson–Keerthi (GJK) algorithm for collision detection of convex shapes
 *	Implementation of GJK is based upon:
 *		https://caseymuratori.com/blog_0003
 *		http://www.dyn4j.org/2010/04/gjk-gilbert-johnson-keerthi/#gjk-minkowski
 *		http://vec3.ca/gjk/implementation/
 *		http://in2gpu.com/2014/05/18/gjk-algorithm-3d/
 */

#pragma once

#define MAX_NUM_ITERATIONS 128	// Helps with better performance for more complicated convex shapes while sacrificing a little on accuracy

#include <Defs.h>
#include <utils/PhysicsUtil.h>

namespace mtrx
{
	class GJKUtil
	{
	public:
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
		static bool UpdateSimplex(Simplex&, glm::vec3&, glm::vec3&);
		// Update the values of the simplex when we have a triangle simplex
		static bool TriangleSimplexUpdate(Simplex&, glm::vec3&, glm::vec3&);
		// Update the values of the simplex when we have a tetraheadron simplex
		static bool TetrahedronSimplexUpdate(Simplex&, glm::vec3&, glm::vec3&);
		// Extra checks for tetrahedron simplexes
		static void TetrahedronChecks(Simplex&, glm::vec3&, glm::vec3&, glm::vec3&, glm::vec3&, glm::vec3&, glm::vec3&);
		
		// Support functionality for convex shape collider vertices
		template<typename Iterator, typename = std::enable_if_t<std::is_same<glm::vec3*, typename std::iterator_traits<Iterator>::value_type>::value>,
			typename Iterator1, typename = std::enable_if_t<std::is_same<glm::vec3*, typename std::iterator_traits<Iterator1>::value_type>::value>>
		static glm::vec3 Support(const Iterator& startVertices1, const Iterator& endVertices1, const Iterator1& startVertices2, const Iterator1& endVertices2, const glm::vec3& direction)
		{
			const glm::vec3* p1 = FarthestPointInDirection(startVertices1, endVertices1, direction);
			const glm::vec3* p2 = FarthestPointInDirection(startVertices2, endVertices2, -direction);
			return *p1 - *p2;
		}

		// Return farthest point with respect to a certain direction
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