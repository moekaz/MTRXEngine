#include <PrecompiledHeader.h>
#include <colliders/BoxCollider.h>
#include <colliders/SphereCollider.h>
#include <colliders/CapsuleCollider.h>

namespace mtrx
{
	BoxCollider::BoxCollider(const glm::vec3& center, const glm::quat& orientation, const glm::vec3& scale) : 
		BoxCollider(Transform(center, orientation, scale))
	{}

	BoxCollider::BoxCollider(const Transform& transform) :
		ConvexShapeCollider(ColliderType::Box, transform), 
		halfExtents(glm::vec3(0.5f * transform.GetScale().x, 0.5f * transform.GetScale().y, 0.5f * transform.GetScale().z))
	{
		// Vertices of a box
		vertices =
		{
			new glm::vec3(-0.5, 0.5, 0.5),
			new glm::vec3(0.5, 0.5, 0.5),
			new glm::vec3(-0.5, -0.5, 0.5),
			new glm::vec3(0.5, -0.5, 0.5),
			new glm::vec3(-0.5, 0.5, -0.5),
			new glm::vec3(0.5, 0.5, -0.5),
			new glm::vec3(-0.5, -0.5, -0.5),
			new glm::vec3(0.5, -0.5, -0.5),
		};


		transformedVertices.resize(vertices.size());
		for (int i = 0; i < vertices.size(); ++i)
		{
			transformedVertices[i] = new glm::vec3();
		}
	}

	BoxCollider::BoxCollider(const BoxCollider& collider1, const BoxCollider& collider2) : ConvexShapeCollider(ColliderType::Box, Transform())
	{
		// TBD: Constructor for box collider of box colliders needs to be implemented
		// Create a bounding box from the 2 other bounding boxes
	}
}