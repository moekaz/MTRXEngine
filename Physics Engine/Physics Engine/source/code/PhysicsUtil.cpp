/*
	Author: Mohamed Kazma
	Description: This will be a util file that will include some functions that i want to run
	Implementation of smallest distance between 2 line segments:
	http://geomalgorithms.com/a07-_distance.html#dist3D_Segment_to_Segment
*/

#include "../headers/PhysicsUtil.h"

namespace PhysicsUtil
{
	// Optimizes 2 cross product calls into 2 dot product ones
	Vector3D TripleCross(Vector3D& a, Vector3D& b, Vector3D& c)
	{
		// (A x B) x C = B(C . A) - A(C . B)
		return b * (c.DotProduct(a)) - a * (c.DotProduct(b));
	}

	// Finding the minimum distance between infinite lines
	float MinDistanceTwoLines(Vector3D& A, Vector3D& B, Vector3D& C, Vector3D& D)
	{
		Vector3D l1 = B - A;	// First direction vector 
		Vector3D l2 = D - C;	// Second direction vector

		//Vector3D P = l1 / 2;
		//Vector3D Q = l2 / 2;
		Vector3D normalPlane = l1.CrossProduct(l2).Normalize();
		if (normalPlane == Vector3D::zero)
		{
			// They are parallel so choose any new vector that is not parallel to one of them and do the cross product for that it should be parallel to both
			Vector3D newVec = l2 + Vector3D(1, 1, 1);
			normalPlane = l1.CrossProduct(newVec);	// If the normal vector is (0,0,0) choose one of the 2 
		}
		std::cout << normalPlane << std::endl;

		return abs((C - A).DotProduct(normalPlane));
	}

	// Finding the minimum distance between 2 segments
	float MinDistanceSquaredTwoSegments(Vector3D& A, Vector3D& B, Vector3D& C, Vector3D& D)
	{
		Vector3D u = B - A;
		Vector3D v = D - C;
		Vector3D w = A - C;
		float a = u.DotProduct(u);
		float b = u.DotProduct(v);
		float c = v.DotProduct(v);
		float d = u.DotProduct(w);
		float e = v.DotProduct(w);
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

		Vector3D distanceVec =  w + (u * sc) - (v * tc);
		return distanceVec.MagnitudeSquared();
	}
	
	float MinDistanceSquaredPointSegment(Vector3D& A, Vector3D& B, Vector3D& C , Vector3D& closest)
	{
		Vector3D AB = B - A;
		Vector3D AC = C - A;
		Vector3D BC = C - B;

		float dot = AC.DotProduct(AB);
		if (dot < 0.0f)
		{
			closest = A;
			std::cout << "Clamped to A" << std::endl;
			// Clamp to A being the closest point
			return AC.MagnitudeSquared();
		}
		else if (BC.DotProduct(AB) > 0.0f)
		{
			closest = B;
			std::cout << "Clamped to B" << std::endl;
			// Clamp B to being the closest point
			return BC.MagnitudeSquared();
		}
		else
		{
			closest = AB.Normalize() * dot;
			std::cout << "Between A and B" << std::endl;
			// Its a point between them so use pythagoras to find it 
			return AC.MagnitudeSquared() - (dot * dot);
		}
	}
}