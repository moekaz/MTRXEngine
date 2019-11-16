#pragma once

namespace mtrx
{
	class Ray
	{
	public:
		Ray(const glm::vec3& startPos = glm::vec3(), const glm::vec3& rayDirection = glm::vec3()) : startPosition(startPos), direction(rayDirection)
		{}

		~Ray() = default;

		glm::vec3 startPosition;
		glm::vec3 direction;

	private:
	};
}