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
			center, glm::angleAxis(0.f, worldUp), scale),
			axes(glm::vec3(0, 0, -1), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0)),
			halfExtents { 0.5f * scale.x, 0.5f * scale.y, 0.5f * scale.z }
	{}

	//AABBCollider::AABBCollider(const AABBCollider& aabb, const AABBCollider& aabb1) : ConvexShapeCollider(ColliderType::AABB, Transform())
	//{
	//	for()
	//}
}