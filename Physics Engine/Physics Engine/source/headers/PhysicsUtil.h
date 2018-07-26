/*
	Author: Mohamed Kazma
	Description: Utility file that would include general functions that can be useful for general use
*/

#pragma once
#ifndef PHYSICSUTIL_H
#define PHYSICSUTIL_H

#include <glm/vec3.hpp>

namespace PhysicsUtil
{
	glm::vec3 TripleCross(glm::vec3& a, glm::vec3& b, glm::vec3& c);						// Calculates the triple cross product of 3 vectors
	float MinDistanceTwoLines(glm::vec3&, glm::vec3&, glm::vec3&, glm::vec3&);				
	float MinDistanceSquaredTwoSegments(glm::vec3&, glm::vec3&, glm::vec3&, glm::vec3&);
	float MinDistanceSquaredPointSegment(glm::vec3& , glm::vec3& , glm::vec3& , glm::vec3&);
}
#endif // !PHYSICSUTIL_H