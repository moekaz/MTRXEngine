#include <PrecompiledHeader.h>
#include <colliders/BoxCollider.h>

namespace mtrx
{
	BoxCollider::BoxCollider(const glm::vec3& center, const glm::quat& orientation, const glm::vec3& scale) : 
		BoxCollider(Transform(center, orientation, scale))
	{}

	BoxCollider::BoxCollider(const Transform& transform) :
		ConvexShapeCollider(ColliderType::Box,
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
		halfExtents { 0.5f * transform.GetScale().x, 0.5f * transform.GetScale().y, 0.5f * transform.GetScale().z }
	{}

	BoxCollider::BoxCollider(const BoxCollider& collider1, const BoxCollider& collider2) : ConvexShapeCollider(ColliderType::Box, Transform())
	{
		// TBD: Constructor for box collider of box colliders needs to be implemented
		// Create a bounding box from the 2 other bounding boxes
	}
}