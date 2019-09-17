/*
	Author: Mohamed Kazma
	Description: Gilbert–Johnson–Keerthi (GJK) algorithm for collision detection of convex shapes
	Implementation of GJK is based upon:
		https://caseymuratori.com/blog_0003
		http://www.dyn4j.org/2010/04/gjk-gilbert-johnson-keerthi/#gjk-minkowski
		http://vec3.ca/gjk/implementation/
		http://in2gpu.com/2014/05/18/gjk-algorithm-3d/
*/

#pragma once

#define MAX_NUM_ITERATIONS 64	// Helps with better performance for more complicated convex shapes while sacrificing a little on accuracy

#include <utils/PhysicsUtil.h>
#include <log/LogManager.h>
#include <Defs.h>

namespace mtrx
{
	// Forward declarations
	class ConvexShapeCollider;

	class GJK
	{
	public:
		// Gilbert-Johnson-Keerthi collision detection algorithm
		static bool Collision(const ConvexShapeCollider&, const ConvexShapeCollider&);

	private:
		// Update the values of the simplex after adding points from support
		static bool UpdateSimplex(Simplex&, glm::vec3&, glm::vec3&);
		// Update the values of the simplex when we have a triangle simplex
		static bool TriangleSimplexUpdate(Simplex&, glm::vec3&, glm::vec3&);
		// Update the values of the simplex when we have a tetraheadron simplex
		static bool TetrahedronSimplexUpdate(Simplex&, glm::vec3&, glm::vec3&);
		// Extra checks for tetrahedron simplexes
		static void TetrahedronChecks(Simplex&, glm::vec3&, glm::vec3&, glm::vec3&, glm::vec3&, glm::vec3&, glm::vec3&);

		static Simplex simplex; // Simplex that stores vertices
	};
}