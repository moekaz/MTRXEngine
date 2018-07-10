/*
	Author: Mohamed Kazma
	Description: Utility file that would include general functions that can be useful for general use
*/

#pragma once
#ifndef PHYSICSUTIL_H
#define PHYSICSUTIL_H

#include "Vector3D.h"

namespace PhysicsUtil
{
	Vector3D TripleCross(Vector3D& a, Vector3D& b, Vector3D& c);						// Calculates the triple cross product of 3 vectors
	float MinDistanceTwoLines(Vector3D&, Vector3D&, Vector3D&, Vector3D&);				
	float MinDistanceSquaredTwoSegments(Vector3D&, Vector3D&, Vector3D&, Vector3D&);
	float MinDistanceSquaredPointSegment(Vector3D& , Vector3D& , Vector3D& , Vector3D&);
}
#endif // !PHYSICSUTIL_H