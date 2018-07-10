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

#define MAX_NUM_ITERATIONS 64

#include "Simplex.h"
#include "Vector3D.h"
#include "PhysicsUtil.h"

// Forward declarations
class ConvexShapeCollider;

class GJK
{
public:
	bool GJKCollision(ConvexShapeCollider&, ConvexShapeCollider&);											// General implementation of GJK

private:
	bool UpdateSimplex(Simplex&, Vector3D&, Vector3D&);														// Update the values of the simplex after adding points from support
	bool TriangleSimplexUpdate(Simplex&, Vector3D&, Vector3D&);												// Update the values of the simplex when we have a triangle simplex
	bool TetrahedronSimplexUpdate(Simplex&, Vector3D&, Vector3D&);											// Update the values of the simplex when we have a tetraheadron simplex
	bool TetrahedronChecks(Simplex&, Vector3D&, Vector3D&, Vector3D&, Vector3D&, Vector3D&, Vector3D&);		// Extra checks for tetrahedron simplexes

protected:
};
#endif // !GJK_H
