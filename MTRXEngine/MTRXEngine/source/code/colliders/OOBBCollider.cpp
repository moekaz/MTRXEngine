#include "PrecompiledHeader.h"

#include "colliders/OOBBCollider.h"

namespace mtrx
{
	OOBBCollider::OOBBCollider(const glm::vec3& center, const glm::quat& orientation, const glm::vec3& scale) :
		OOBBCollider(Transform(center, orientation, scale))
	{}

	OOBBCollider::OOBBCollider(const Transform& transform) :
		ConvexShapeCollider(ColliderType::OOBB,
			{
				new glm::vec3(-0.5, 0.5, 0.5),
				new glm::vec3(0.5, 0.5, 0.5),
				new glm::vec3(-0.5, -0.5, 0.5),
				new glm::vec3(0.5, -0.5, 0.5),
				new glm::vec3(-0.5, 0.5, -0.5),
				new glm::vec3(0.5, 0.5, -0.5),
				new glm::vec3(-0.5, -0.5, -0.5),
				new glm::vec3(0.5, -0.5, -0.5),
			},
			transform),
			halfExtents{ 0.5f * transform.GetScale().x, 0.5f * transform.GetScale().y, 0.5f * transform.GetScale().z }
	{}
}