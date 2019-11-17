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
}