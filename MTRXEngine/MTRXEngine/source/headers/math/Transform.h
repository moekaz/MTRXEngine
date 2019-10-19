#pragma once

#include <PrecompiledHeader.h>
#include <Defs.h>

namespace mtrx
{
	class Transform
	{
	public:
		Transform(const glm::vec3& position = glm::vec3(), const glm::quat& orientation = glm::angleAxis(0.f, worldUp), const glm::vec3& scale = glm::vec3(1, 1, 1)) :
			position(position), orientation(orientation), scale(scale)
		{}

		~Transform() = default;

		inline void Translate(const glm::vec3& translationVec) { position += translationVec; }
		inline void Rotate(const glm::quat& rotation) { orientation = rotation * orientation; }

		// Setters
		inline void SetPosition(const glm::vec3& pos) { position = pos; }
		inline void SetOrientation(const glm::quat& orientation) { this->orientation = orientation; }
		inline void SetScale(const glm::vec3& scale) { this->scale = scale; }

		// Getters
		inline const glm::vec3& GetPosition() const { return position; }
		inline const glm::quat& GetOrientation() const { return orientation; }
		inline const glm::vec3& GetScale() const { return scale; }

		// Non-const getters
		inline glm::vec3& GetPosition() { return position; }
		inline glm::quat& GetOrientation() { return orientation; }
		inline glm::vec3& GetScale() { return scale; }

	private:
		glm::vec3 position;
		glm::quat orientation;
		glm::vec3 scale;
	};
}
