/*
	Author: Mohamed Kazma
	Description: This will be a util file that will include some functions that i want to run
*/

#include "../headers/Utils.h"

namespace Utils
{
	// Optimizes 2 cross product calls into 2 dot product ones
	Vector3D TripleCross(Vector3D& a, Vector3D& b, Vector3D& c)
	{
		// (A x B) x C = B(C . A) - A(C . B)
		return b * (c.DotProduct(a)) - a * (c.DotProduct(b));
	}
}