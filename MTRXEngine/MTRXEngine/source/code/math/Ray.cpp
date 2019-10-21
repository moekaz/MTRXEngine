/*
	Author: Mohamed Kazma
	Description: Implementation of a ray
*/

#include <PrecompiledHeader.h>
#include <math/Ray.h>

namespace mtrx
{
	Ray::Ray(const glm::vec3& startPos, const glm::vec3& rayDirection) : startPosition(startPos), direction(rayDirection) 
	{}
}