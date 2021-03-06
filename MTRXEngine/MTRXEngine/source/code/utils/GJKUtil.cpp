#include <PrecompiledHeader.h>
#include <utils/GJKUtil.h>

namespace mtrx
{
	Simplex GJKUtil::simplex;

	bool GJKUtil::UpdateSimplex(Simplex& simplex, glm::vec3& direction, glm::vec3& a)
	{
		switch (simplex.size) // The simplex will never have a size less than 2 or greater than 3 
		{
			case 2:	// Triangle
			{
				return TriangleSimplexUpdate(simplex, direction, a);
			}
			case 3: // Tetrahedron
			{
				return TetrahedronSimplexUpdate(simplex, direction, a);
			}
			default:	// Something went wrong
			{
				MTRX_ERROR("Simplex has wrong size");
				return false;
			}
		}
	}

	bool GJKUtil::TriangleSimplexUpdate(Simplex& simplex, glm::vec3& direction, glm::vec3& a)
	{
		glm::vec3 AB = *simplex.b - a;
		glm::vec3 AC = *simplex.c - a;
		glm::vec3 AO = -a;
		glm::vec3 ABC = glm::cross(AB, AC); // The normal of the triangle
		glm::vec3 ABP = glm::cross(AB, ABC); // Calculate a vector inside the triangle away from AB
		glm::vec3 ACP = glm::cross(ABC, AC); // Same as the one above

		if (glm::dot(ABP, AO) > 0) // C is not part of the simplex anymore
		{
			simplex.c = simplex.b;
			simplex.b = &a;
			direction = PhysicsUtil::TripleCross(AB, AO, AB);
			simplex.size = 2;
		}
		else if (glm::dot(ACP, AO) > 0) // B is no longer part of the simplex
		{
			simplex.b = &a;
			direction = PhysicsUtil::TripleCross(AC, AO, AC);
			simplex.size = 2;
		}
		else if (glm::dot(ABC, AO) > 0) // The origin is above ABC
		{
			simplex.d = simplex.c;
			simplex.c = simplex.b;
			simplex.b = &a;
			direction = ABC;
			simplex.size = 3;
		}
		else // The origin is below ABC
		{
			simplex.d = simplex.b;
			simplex.b = &a;
			direction = -ABC;
			simplex.size = 3;
		}

		return false;
	}

	bool GJKUtil::TetrahedronSimplexUpdate(Simplex& simplex, glm::vec3& direction, glm::vec3& a)
	{
		glm::vec3 AO = -a;
		glm::vec3 AB = *simplex.b - a;
		glm::vec3 AC = *simplex.c - a;
		glm::vec3 AD = *simplex.d - a;
		glm::vec3 ABC = glm::cross(AB, AC);
		glm::vec3 ACD = glm::cross(AC, AD);
		glm::vec3 ADB = glm::cross(AD, AB);
		float ABCdotAO = glm::dot(ABC, AO);
		float ACDdotAO = glm::dot(ACD, AO);
		float ADBdotAO = glm::dot(ADB, AO);

		if (ABCdotAO <= 0 && ACDdotAO <= 0 && ADBdotAO <= 0) return true;	// The origin is inside the tetrahedron

		if (ABCdotAO > 0) // The origin is in front of ABC
		{
			TetrahedronChecks(simplex, AO, AB, AC, ABC, direction, a);
		}
		if (ACDdotAO > 0) // The origin is in front of ACD rotate ACD to become ABC
		{
			simplex.b = simplex.c;
			simplex.c = simplex.d;

			AB = AC;
			AD = AC;
			ABC = ACD;

			TetrahedronChecks(simplex, AO, AB, AC, ABC, direction, a);
		}
		if (ADBdotAO > 0) // The origin is in front of ADB 
		{
			simplex.d = simplex.b;
			simplex.b = simplex.c;

			AB = AD;
			AC = AB;
			ABC = ADB;

			TetrahedronChecks(simplex, AO, AB, AC, ABC, direction, a);
		}

		return false;
	}

	void GJKUtil::TetrahedronChecks(Simplex& simplex, glm::vec3& AO, glm::vec3& AB, glm::vec3& AC, glm::vec3& ABC, glm::vec3& direction, glm::vec3& a)
	{
		if (glm::dot(glm::cross(AB, ABC), AO) > 0) // Just like the triangle check use the cross product away from AB
		{
			simplex.c = simplex.b;
			simplex.b = &a;

			// We have lost d in this process so we need to rebuild the triangle
			simplex.size = 2;
			direction = PhysicsUtil::TripleCross(AB, AO, AB);
		}
		else if (glm::dot(glm::cross(ABC, AC), AO) > 0) // Same as the top one
		{
			simplex.b = &a;

			simplex.size = 2;	// We also need to rebuild the triangle as well
			direction = PhysicsUtil::TripleCross(AC, AO, AC);
		}
		else // Build a new tetrahedron 
		{
			simplex.d = simplex.c;
			simplex.c = simplex.b;
			simplex.b = &a;

			simplex.size = 3;
			direction = ABC;	// ABC is what is left
		}
	}
}