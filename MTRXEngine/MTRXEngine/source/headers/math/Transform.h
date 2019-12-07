#pragma once

#include <PrecompiledHeader.h>
#include <Defs.h>

namespace mtrx
{
	/**
	 * @brief Wrapper implementation of a transform that holds position, orientation, scale values and some functionality based on these values
	 * 
	 */
	class Transform
	{
	public:

		/**
		 * @brief Construct a new Transform object
		 * 
		 * @param position 
		 * @param orientation 
		 * @param scale 
		 */
		Transform(const glm::vec3& position = glm::vec3(), const glm::quat& orientation = glm::angleAxis(0.f, worldUp), const glm::vec3& scale = glm::vec3(1, 1, 1)) :
			position(position), orientation(orientation), scale(scale)
		{}

		/**
		 * @brief Destroy the Transform object
		 * 
		 */
		~Transform() = default;

		/**
		 * @brief Translate the position vector 
		 * 
		 * @param translationVec Vector used to translate the position of the transform
		 */
		inline void Translate(const glm::vec3& translationVec) { position += translationVec; }

		/**
		 * @brief Rotate the orientation value
		 * 
		 * @param rotation The rotation quaternion that we want to rotate the orientation with
		 */
		inline void Rotate(const glm::quat& rotation) { orientation = rotation * orientation; }

		// Setters

		/**
		 * @brief Set the Position vector
		 * 
		 * @param pos The new position value
		 */
		inline void SetPosition(const glm::vec3& pos) { position = pos; }

		/**
		 * @brief Set the Orientation quaternion
		 * 
		 * @param orientation The new orientation value
		 */
		inline void SetOrientation(const glm::quat& orientation) { this->orientation = orientation; }

		/**
		 * @brief Set the Scale vector
		 * 
		 * @param scale The new scale value
		 */
		inline void SetScale(const glm::vec3& scale) { this->scale = scale; }

		// Getters

		/**
		 * @brief Get the Position vector
		 * 
		 * @return const glm::vec3& Position value
		 */
		inline const glm::vec3& GetPosition() const { return position; }

		/**
		 * @brief Get the Orientation quaternion
		 * 
		 * @return const glm::quat& Orientation value
		 */
		inline const glm::quat& GetOrientation() const { return orientation; }

		/**
		 * @brief Get the Scale vector
		 * 
		 * @return const glm::vec3& Scale value
		 */
		inline const glm::vec3& GetScale() const { return scale; }

		// Non-const getters

		/**
		 * @brief Get the Position vector
		 * 
		 * @return glm::vec3& Position value
		 */
		inline glm::vec3& GetPosition() { return position; }

		/**
		 * @brief Get the Orientation quaternion
		 * 
		 * @return glm::quat& Orientation value 
		 */
		inline glm::quat& GetOrientation() { return orientation; }

		/**
		 * @brief Get the Scale vctor
		 * 
		 * @return glm::vec3& Scale vector
		 */
		inline glm::vec3& GetScale() { return scale; }

	private:
		glm::vec3 position;
		glm::quat orientation;
		glm::vec3 scale;
	};
}
