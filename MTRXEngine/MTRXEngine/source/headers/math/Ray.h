#pragma once

namespace mtrx
{
	#define MAX_RAY_SIZE 10000.f

	class Ray
	{
	public:
		Ray(const glm::vec3& startpos = glm::vec3(), const glm::vec3& rayDirection = glm::vec3());
		~Ray();

		glm::vec3 startPosition;	// The position where the ray starts at
		glm::vec3 direction;		// The direction the ray will go in

	private:
	protected:
	};
}