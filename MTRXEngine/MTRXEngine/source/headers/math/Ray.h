#pragma once

namespace mtrx
{
	/**
	 * @brief Implementation of a ray
	 * 
	 */
	class Ray
	{
	public:
		glm::vec3 startPosition;
		glm::vec3 direction;

		/**
		 * @brief Construct a new Ray object
		 * 
		 * @param startPos The start position of the ray
		 * @param rayDirection A normalized vector representing the direction of the ray
		 */
		Ray(const glm::vec3& startPos = glm::vec3(), const glm::vec3& rayDirection = glm::vec3()) : startPosition(startPos), direction(rayDirection)
		{}

		/**
		 * @brief Destroy the Ray object
		 * 
		 */
		~Ray() = default;

	private:
	};
}