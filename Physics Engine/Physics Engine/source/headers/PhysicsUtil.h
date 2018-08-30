/*
	Author: Mohamed Kazma
	Description: Utility file that would include general functions that can be useful for general use
*/

#pragma once
#ifndef PHYSICSUTIL_H
#define PHYSICSUTIL_H

#include <iostream>
#include <vector>
#include <map>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>

#include "Ray.h"
#include "CollisionUtil.h"
#include "Collider.h"

namespace PhysicsUtil
{
	glm::vec3 TripleCross(glm::vec3& a, glm::vec3& b, glm::vec3& c);						// Calculates the triple cross product of 3 vectors
	float MinDistanceTwoLines(glm::vec3&, glm::vec3&, glm::vec3&, glm::vec3&);				
	float MinDistanceSquaredTwoSegments(glm::vec3&, glm::vec3&, glm::vec3&, glm::vec3&);
	float MinDistanceSquaredPointSegment(glm::vec3& , glm::vec3& , glm::vec3& , glm::vec3&);
	float MinDistanceSquaredPointRay(glm::vec3&, glm::vec3&, glm::vec3&, glm::vec3&);
	float MinDistanceSquaredLineSegmentRay(glm::vec3&, glm::vec3&, glm::vec3&, glm::vec3&);
	Collider* RaycastFiltered(std::map<int, Collider*>& colliders, std::vector<Collider*>& filterColliders, glm::vec3& rayStartPosition, glm::vec3& rayDirection);
	Collider* RaycastUnfiltered(std::map<int, Collider*>& colliders, glm::vec3& rayStartPosition, glm::vec3& rayDirection);
}
#endif // !PHYSICSUTIL_H