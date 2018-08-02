/*
	Author: Mohamed Kazma
	Description: A ray that will be used for raycasting
*/

#include <glm/vec3.hpp>

class Ray
{
public:
	Ray();
	~Ray();

	glm::vec3 startPosition;	// The position where the ray starts at
	glm::vec3 direction;		// The direction the ray will go in

private:
protected:
};