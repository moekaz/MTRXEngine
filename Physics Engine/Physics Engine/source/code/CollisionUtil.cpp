/*
	Author: Mohamed Kazma
	Description: Util file that includes implementations of collider collision detection
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
		std::vector<Vector3D*> simplex;	// We will need to store the simplex
		Vector3D a, b, c, d, ab, ao;
		Vector3D searchDirection = convexCollider1.center - convexCollider2.center;	// It doesn't really matter
		searchDirection = Vector3D(0 , -1 , 0);
		a = convexCollider1.Support(convexCollider2, searchDirection);
		//std::cout << "first vector:" << std::endl << a << std::endl;
		searchDirection = ao = -a;	// Don't have a minus operator atm

		simplex.push_back(&a);
	
		for (int i = 0; i < MAX_NUM_ITERATIONS; i++)
		{
			Vector3D p = convexCollider1.Support(convexCollider2, searchDirection);
			//std::cout << "new vectors:" << std::endl << p << std::endl;

			simplex.push_back(&p);	// Add a new point to the simplex
			std::cout << simplex.size() << std::endl;

			if ((*simplex[simplex.size() - 1]).DotProduct(searchDirection) < 0)
			{
				std::cout << "WE CANNOT FIND A POINT PAST THE ORIGIN" << std::endl;
				return false;		// We cannot have a collision
			}

			if (UpdateSimplex(simplex, searchDirection))
			{
				std::cout << "THE ORIGIN IS INSIDE OUR TETRAHEDRON" << std::endl;
				return true;		// Update the simplex and set a new direction vector
			}
		}

		return false;
	}

	// Updates the simplex
	bool UpdateSimplex(std::vector<Vector3D*>& simplex, Vector3D& direction)
	{
		bool collision = false;
		// The simplex will hold at most 2 points at all times
		if (simplex.size() == 2)	// line Segment
		{
			std::cout << "LINE SEGMENT SIMPLEX CHECK" << std::endl;
			collision = LineSimplexUpdate(simplex, direction);
		}
		else if (simplex.size() == 3)	// Triangle
		{
			std::cout << "TRIANGLE SIMPLEX CHECK" << std::endl;
			collision = TriangleSimplexUpdate(simplex, direction);
		}
		else if (simplex.size() == 4) // Tetrahedron
		{
			std::cout << "TETRAHEDRON SIMPLEX CHECK" << std::endl;
			collision = TetrahedronSimplexUpdate(simplex, direction);
		}
		else if (simplex.size() > 4)
		{
			std::cout << "HOUSTON WE HAVE A PROBLEM" << std::endl;
		}

		return collision;
	}
	
	// Line simplex update
	bool LineSimplexUpdate(std::vector<Vector3D*>& simplex, Vector3D& direction)
	{
		Vector3D& A = *simplex[1]; // Last point added
		Vector3D& B = *simplex[0];	// First point added
		Vector3D AB = B - A;
		Vector3D AO = -A;

		direction = AB.CrossProduct(AO).CrossProduct(AB);

		/*
		if (AB.DotProduct(AO) > 0) direction = AB.CrossProduct(AO).CrossProduct(AB);
		else direction = AO;
		*/

		return false;
	}
	
	// Triangle simplex update
	bool TriangleSimplexUpdate(std::vector<Vector3D*>& simplex, Vector3D& direction)
	{
		Vector3D AB = *simplex[1] - *simplex[0];
		Vector3D AC = *simplex[2] - *simplex[0];
		Vector3D AO = -*simplex[0];	
		direction = AB.CrossProduct(AC);			// The normal of the triangle

		if (direction.DotProduct(AO) < 0) direction *= -1;	// If it is not closer to the origin flip to use the other normal

		/*
		Vector3D& A = simplex[simplex.size];
		Vector3D& B = simplex[1];
		Vector3D& C = simplex[0];

		Vector3D AO = Vector3D::zero - A;
		Vector3D AB = B - A;
		Vector3D AC = C - A;

		Vector3D ABC = AB.CrossProduct(AC);	// Get the normal of the triangle's plane

		if (ABC.CrossProduct(AC).DotProduct(AO) > 0)
		{
			if (AC.DotProduct(AO) > 0)
			{
				simplex.erase(simplex.begin() + 1);	// Remove B as the simplex is now AC
				direction = AC.CrossProduct(AO).CrossProduct(AC);
			}
			else if (AB.DotProduct(AO) > 0)
			{
				simplex.erase(simplex.begin());	// Remove C as the simplex is now AB
				direction = AB.CrossProduct(AO).CrossProduct(AB);
			}
		}
		else if (AB.CrossProduct(ABC).DotProduct(AO) > 0)
		{
			if (AB.DotProduct(AO) > 0)
			{
				simplex.erase(simplex.begin());	// Remove C as the simplex is now AB
				direction = AB.CrossProduct(AO).CrossProduct(AB);
			}
			else if (ABC.DotProduct(AO) > 0)
			{
				// Simplex i think then remains the same [ABC]
				direction = ABC;
			}
			else
			{
				// Swap B and C simplex is now [ACB]
				Vector3D& temp = simplex[1]; // this is B
				simplex[1] = simplex[0];
				simplex[0] = temp;
				direction = Vector3D::zero - ABC;
			}
		}
		else if (AB.DotProduct(AO) > 0)
		{
			simplex.erase(simplex.begin());	// Remove C as the simplex is now AB
			direction = AB.CrossProduct(AO).CrossProduct(AB);
		}
		else
		{
			// The simplex is just then AO
			simplex.clear();
			simplex.push_back(A);
			direction = AO;
		}
		*/

		return false;
	}
	
	// Tetrahedron simplex update
	bool TetrahedronSimplexUpdate(std::vector<Vector3D*>& simplex , Vector3D& direction)
	{
		Vector3D& A = *simplex[0];	
		Vector3D& B = *simplex[1];
		Vector3D& C = *simplex[2];
		Vector3D& D = *simplex[3];	// D is the top of the tetrahedron
		
		Vector3D DA = A - D;
		Vector3D DB = B - D;
		Vector3D DC = C - D;

		// We have already checked the triangle ABC so we will check the other triangles
		Vector3D DO = -D;	// We will use that to check if we are closer to the origin

		Vector3D ABD, ACD, BCD;
		
		ABD = DA.CrossProduct(DB);		// Normal of ABD
		ACD = DC.CrossProduct(DA);		// Normal of ACD
		BCD = DB.CrossProduct(DC);		// Normal of BCD

		if (ABD.DotProduct(DO) > 0)
		{
			std::cout << "Origin is outside ABD" << std::endl;
			// Origin is outside ABD remove C and make that normal ABD the new direction
			simplex.erase(simplex.begin() + 2);	// Removing C
			direction = ABD;
		}
		else if (ACD.DotProduct(DO) > 0)
		{
			std::cout << "Origin is outside ACD" << std::endl;
			// Origin is outside ACD remove B and make the normal of ACD the new direction
			simplex.erase(simplex.begin() + 1);	// Remove B
			direction = ACD;
		}
		else if (BCD.DotProduct(DO) > 0)
		{
			std::cout << "Origin is outside BCD" << std::endl;
			// Origin is outside BCD remove A and make the normal of BCD the new direction
			simplex.erase(simplex.begin());	// Remove A
			direction = BCD;
		}
		else
		{
			std::cout << "Origin is inside the tetrahedron" << std::endl;
			return true; 	// It is inside the tetrahedron So we have an intersection
		}

		return false; // If we do not get to the final else then we do not have an intersection yet 
	}

	// Helpful for collision response
	void EPA()
	{
	}
}