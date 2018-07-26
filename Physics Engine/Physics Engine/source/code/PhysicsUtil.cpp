/*
	Author: Mohamed Kazma
	Description: This will be a util file that will include some functions that a physics engine will generally need
	Implementation of smallest distance between 2 line segments:
		http://geomalgorithms.com/a07-_distance.html#dist3D_Segment_to_Segment
*/

#include "../headers/PhysicsUtil.h"

namespace PhysicsUtil
{
	// Optimizes 2 cross product calls into 2 dot product ones
	glm::vec3 TripleCross(glm::vec3& a, glm::vec3& b, glm::vec3& c)
	{
		// (A x B) x C = B(C . A) - A(C . B)
		return b * (glm::dot(c , a)) - a * (glm::dot(c,b));
	}

	// Finding the minimum distance between infinite lines
	float MinDistanceTwoLines(glm::vec3& A, glm::vec3& B, glm::vec3& C, glm::vec3& D)
	{
		glm::vec3 l1 = B - A;	// First direction vector 
		glm::vec3 l2 = D - C;	// Second direction vector

		//glm::vec3 P = l1 / 2;
		//glm::vec3 Q = l2 / 2;
		glm::vec3 normalPlane = glm::normalize(glm::cross(l1, l2));

		if (normalPlane == glm::vec3())
		{
			// They are parallel so choose any new vector that is not parallel to one of them and do the cross product for that it should be parallel to both
			glm::vec3 newVec = l2 + glm::vec3(1, 1, 1);
			normalPlane = glm::cross(l1, newVec);	// If the normal vector is (0,0,0) choose one of the 2 
		}

		//std::cout << normalPlane << std::endl;

		return abs(glm::dot(C - A , normalPlane));
	}

	// Finding the minimum distance between 2 line segments
	float MinDistanceSquaredTwoSegments(glm::vec3& A, glm::vec3& B, glm::vec3& C, glm::vec3& D)
	{
		glm::vec3 u = B - A;
		glm::vec3 v = D - C;
		glm::vec3 w = A - C;
		float a = glm::dot(u, u);
		float b = glm::dot(u, v);
		float c = glm::dot(v, v);
		float d = glm::dot(u, w);
		float e = glm::dot(v, w);
		float _D = a * c - b * b;
		float sc = 0 , sn = 0;
		float sd = _D;
		float tc = 0, tn = 0;
		float td = _D;

		// Segments almost parallel
		if (_D < std::numeric_limits<float>::epsilon())
		{
			sn = 0.0f;
			sd = 1.0f;
			tn = e;
			td = c;
		}
		else
		{
			sn = b * e - c * d;
			tn = a * e - b * d;

			if (sn < 0.0f)
			{
				sn = 0.0;
				tn = e;
				td = c;
			}
			else if (sn > sd)
			{
				sn = sd;
				tn = e + b;
				td = c;
			}
		}

		if (tn < 0.0f)
		{
			tn = 0.0f;

			if (-d < 0.0f) sn = 0.0f;
			else if (-d > a) sn = sd;
			else
			{
				sn = -d;
				sd = a;
			}
		}
		else if (tn > td)
		{
			tn = td;

			if (-d + b < 0.0f) sn = 0.0f;
			else if (-d + b > a) sn = sd;
			else
			{
				sn = -d + b;
				sd = a;
			}
		}

		if (abs(sc) < std::numeric_limits<float>::epsilon()) sc = 0;
		else sn / sd;
		if (abs(tc) < std::numeric_limits<float>::epsilon()) tc = 0;
		else tn / td;

		glm::vec3 distanceVec =  w + (u * sc) - (v * tc);
		return glm::dot(distanceVec, distanceVec);
	}
	
	// Minimum distance between a point and a line segment
	float MinDistanceSquaredPointSegment(glm::vec3& A, glm::vec3& B, glm::vec3& C , glm::vec3& closest)
	{
		glm::vec3 AB = B - A;
		glm::vec3 AC = C - A;
		glm::vec3 BC = C - B;

		float dot = glm::dot(AC, AB);
		if (dot < 0.0f)
		{
			closest = A;
			std::cout << "Clamped to A" << std::endl;
			// Clamp to A being the closest point
			return glm::dot(AC, AC);
		}
		else if (glm::dot(BC , AB) > 0.0f)
		{
			closest = B;
			std::cout << "Clamped to B" << std::endl;
			// Clamp B to being the closest point
			return glm::dot(BC, BC);
		}
		else
		{
			closest = glm::normalize(AB) * dot;
			std::cout << "Between A and B" << std::endl;
			// Its a point between them so use pythagoras to find it 
			return glm::dot(AC, AC) - (dot * dot);
		}
	}
}