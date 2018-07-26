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
#ifndef GJK_H
#define GJK_H

#define MAX_NUM_ITERATIONS 64	// Helps with better performance for more complicated convex shapes while sacrificing a little on accuracy

#include <glm/vec3.hpp>

#include "Simplex.h"
#include "PhysicsUtil.h"

// Forward declarations
class ConvexShapeCollider;

class GJK
{
public:
	bool GJKCollision(ConvexShapeCollider&, ConvexShapeCollider&);												// General implementation of GJK

private:
	bool UpdateSimplex(Simplex&, glm::vec3&, glm::vec3&);														// Update the values of the simplex after adding points from support
	bool TriangleSimplexUpdate(Simplex&, glm::vec3&, glm::vec3&);												// Update the values of the simplex when we have a triangle simplex
	bool TetrahedronSimplexUpdate(Simplex&, glm::vec3&, glm::vec3&);											// Update the values of the simplex when we have a tetraheadron simplex
	bool TetrahedronChecks(Simplex&, glm::vec3&, glm::vec3&, glm::vec3&, glm::vec3&, glm::vec3&, glm::vec3&);	// Extra checks for tetrahedron simplexes

protected:
};
#endif // !GJK_H
