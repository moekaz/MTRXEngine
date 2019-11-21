#include "PrecompiledHeader.h"

#include "colliders/AABBCollider.h"

namespace mtrx
{
	AABBCollider::AABBCollider(const glm::vec3& center, const glm::vec3& scale) :
		ConvexShapeCollider(ColliderType::AABB,
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
			center, glm::angleAxis(0.f, glm::vec3(0, 1, 0)), scale),
			halfExtents { 0.5f * scale.x, 0.5f * scale.y, 0.5f * scale.z }
	{}
}