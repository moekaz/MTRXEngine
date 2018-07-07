/*
	Author: Mohamed Kazma
	Description: Util file that includes implementations of collider collision detection
	Implementation of GJK is based upon:
	https://caseymuratori.com/blog_0003
	http://www.dyn4j.org/2010/04/gjk-gilbert-johnson-keerthi/#gjk-minkowski
	http://vec3.ca/gjk/implementation/
	http://in2gpu.com/2014/05/18/gjk-algorithm-3d/
*/

// Fix for cyclic dependencies
#include "../headers/CollisionUtil.h"
#include "../headers/BoxCollider.h"
#include "../headers/SphereCollider.h"
//#include "../headers/CapsuleCollider.h"
//#include "../headers/MeshCollider.h"
#include "../headers/ConvexShapeCollider.h"
#include "../headers/Vector3D.h"

#define MAX_NUM_ITERATIONS 64

namespace CollisionUtil
{
	// Sphere sphere collision detection
	bool SphereSphereCollision(SphereCollider& sphereCollider1, SphereCollider& sphereCollider2)
	{
		Vector3D diff = sphereCollider1.center - sphereCollider2.center;
		return diff.MagnitudeSquared() <= (sphereCollider1.radius + sphereCollider2.radius) * (sphereCollider1.radius + sphereCollider2.radius);
	}

	// Sphere box collision detection
	bool SphereBoxCollision(SphereCollider& sphereCollider, BoxCollider& boxCollider)
	{
		return false;
	}

	bool SphereCapsuleCollision()
	{
		return false;
	}

	bool SphereMeshCollision()
	{
		return false;
	}

	bool CollisionUtil::BoxBoxCollision()
	{
		return false;
	}

	bool BoxCapsuleCollision()
	{
		return false;
	}

	bool BoxMeshCollision()
	{
		return false;
	}

	bool CapsuleCapsuleCollision()
	{
		return false;
	}

	bool CapsuleMeshCollision()
	{
		return false;
	}

	bool MeshMeshCollision()
	{
		return false;
	}

	bool ConvexShapeCollision(ConvexShapeCollider& convexCollide1, ConvexShapeCollider& convexCollider2)
	{
		return false;
	}

	// Gilbert-Johnson-Keerthi collision detection algorithm for collision
	bool GJK(ConvexShapeCollider& convexCollider1, ConvexShapeCollider& convexCollider2)
	{
		Simplex simplex;
		Vector3D searchDirection = Vector3D(-1, 0, 0);

		simplex.c = convexCollider1.Support(convexCollider2, searchDirection);

		searchDirection = -simplex.c;	// Negative direction

		simplex.b = convexCollider1.Support(convexCollider2, searchDirection);

		if (simplex.b.DotProduct(searchDirection) < 0) return false;

		Vector3D BC = simplex.c - simplex.b;
		Vector3D BO = -simplex.b;

		searchDirection = TripleCross(BC, BO, BC);

		simplex.size = 2;	// Simplex has 2 points

		for (int i = 0; i < MAX_NUM_ITERATIONS; i++)
		{
			Vector3D a = convexCollider1.Support(convexCollider2, searchDirection);

			std::cout << "Iterations: " << i << std::endl;

			if (a.DotProduct(searchDirection) < 0)
			{
				std::cout << "WE CANNOT FIND A POINT PAST THE ORIGIN" << std::endl;
				return false;		// We cannot have a collision
			}

			if (UpdateSimplex(simplex, searchDirection, a))
			{
				std::cout << "THE ORIGIN IS INSIDE OUR TETRAHEDRON" << std::endl;
				return true;		// Update the simplex and set a new direction vector
			}
		}

		return true;
	}

	// Updates the simplex
	bool UpdateSimplex(Simplex& simplex, Vector3D& direction, Vector3D& a)
	{
		bool collision = false;

		if (simplex.size == 2)	// Triangle
		{
			std::cout << "TRIANGLE SIMPLEX CHECK" << std::endl;
			collision = TriangleSimplexUpdate(simplex, direction, a);
		}
		else if (simplex.size == 3) // Tetrahedron
		{
			std::cout << "TETRAHEDRON SIMPLEX CHECK" << std::endl;
			collision = TetrahedronSimplexUpdate(simplex, direction, a);
		}
		else if (simplex.size > 3)
		{
			std::cout << "HOUSTON WE HAVE A PROBLEM" << std::endl;
		}

		return collision;
	}

	// Triangle simplex update
	bool TriangleSimplexUpdate(Simplex& simplex, Vector3D& direction, Vector3D& a)
	{
		Vector3D AB = simplex.b - a;
		Vector3D AC = simplex.c - a;
		Vector3D AO = -a;

		Vector3D ABC = AB.CrossProduct(AC);			// The normal of the triangle
		Vector3D ABP = AB.CrossProduct(ABC);		// Calculate a vector inside the triangle away from AB
		Vector3D ACP = ABC.CrossProduct(AC);		// Same as the one above

		if (ABP.DotProduct(AO) > 0)
		{
			// C is not part of the simplex anymore
			simplex.c = simplex.b;
			simplex.b = a;
			direction = TripleCross(AB, AO, AB);
		}
		else if (ACP.DotProduct(AO) > 0)
		{
			// B is no longer part of the simplex
			simplex.b = a;
			direction = TripleCross(AC , AO , AC);
		}
		else if (ABC.DotProduct(AO) > 0)
		{
			// The origin is above ABC
			simplex.d = simplex.c;
			simplex.c = simplex.b;
			simplex.b = a;
			direction = ABC;
		}
		else
		{
			// The origin is below ABC
			simplex.d = simplex.b;
			simplex.b = a;
			direction = -ABC;
		}

		simplex.size = 3;	// Simplex is now of size 3

		return false;
	}

	// Tetrahedron simplex update
	bool TetrahedronSimplexUpdate(Simplex& simplex, Vector3D& direction, Vector3D& a)
	{
		Vector3D AO = -a;
		Vector3D AB = simplex.b - a;
		Vector3D AC = simplex.c - a;
		Vector3D AD = simplex.d - a;

		Vector3D ABC = AB.CrossProduct(AC);
		Vector3D ACD = AC.CrossProduct(AD);
		Vector3D ADB = AD.CrossProduct(AB);

		if (ABC.DotProduct(AO) <= 0 && ACD.DotProduct(AO) <= 0 && ADB.DotProduct(AO) <= 0) return true;	// The origin is inside the tetrahedron

		if (ABC.DotProduct(AO) > 0)
		{
			// The origin is in front of ABC
			TetrahedronChecks(simplex, AO, AB, AC, ABC, direction, a);
		}
		if (ACD.DotProduct(AO) > 0)
		{
			// The origin is in front of ACD rotate ACD to become ABC
			simplex.b = simplex.c;
			simplex.c = simplex.d;

			AB = AC; 
			AD = AC;
			ABC = ACD;

			TetrahedronChecks(simplex, AO, AB, AC, ABC, direction, a);
		}
		if (ADB.DotProduct(AO) > 0)
		{
			// The origin is in front of ADB 
			simplex.d = simplex.b;
			simplex.b = simplex.c;

			AB = AD;
			AC = AB;
			ABC = ADB;

			TetrahedronChecks(simplex, AO, AB, AC, ABC, direction, a);
		}
		
		std::cout << "degenerate simplex something went wrong" << std::endl;
	}

	bool TetrahedronChecks(Simplex& simplex , Vector3D& AO, Vector3D& AB, Vector3D& AC, Vector3D& ABC, Vector3D& direction , Vector3D& a)
	{
		// This will always return false
		if (AB.CrossProduct(ABC).DotProduct(AO) > 0)
		{
			// Just like the triangle check use the cross product away from AB
			simplex.c = simplex.b;
			simplex.b = a;

			simplex.size = 2; // We have lost d in this process so we need to rebuild the triangle
			direction = TripleCross(AB , AO , AB);
		}
		else if (ABC.CrossProduct(AC).DotProduct(AO) > 0)
		{
			// Same as the top one
			simplex.b = a;

			simplex.size = 2;	// We also need to rebuild the triangle as well
			direction = TripleCross(AC, AO, AC);
		}
		else
		{
			// Build a new tetrahedron 
			simplex.d = simplex.c;
			simplex.c = simplex.b;
			simplex.b = a;

			direction = ABC;	// ABC is what is left

			simplex.size = 3;
		}

		return false;
	}

	// Optimizes 2 cross product calls into 2 dot product ones
	Vector3D TripleCross(Vector3D& a , Vector3D& b , Vector3D& c)
	{
		// (A x B) x C = B(C . A) - A(C . B)
		return b * (c.DotProduct(a)) - a * (c.DotProduct(b));
	}

	// Helpful for collision response
	// Expanding Polytype Algorithm
	void EPA()
	{
	}
}