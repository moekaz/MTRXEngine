/*
	Author: Mohamed Kazma
	Description: Implementation of a capsule collider
*/

#include <PrecompiledHeader.h>

#include <colliders/CapsuleCollider.h>
//#include <colliders/BoxCollider.h>
//#include <colliders/SphereCollider.h>

namespace mtrx
{
	// TBD: This will not work need to factor in orientation and scale of the capsule (need to fix this pretty quick)
	CapsuleCollider::CapsuleCollider(const glm::vec3& center, const glm::quat& orientation, const glm::vec3& scale, float radii, float height) :
		Collider(ColliderType::Capsule, center, orientation, scale), height(height), A(center - glm::vec3(0, height / 2, 0)),
		B(center - glm::vec3(0, height / 2, 0)), radii(radii)
	{}

	CapsuleCollider::CapsuleCollider(const Transform& transform, float radii, float height) :
		Collider(ColliderType::Capsule, transform), height(height), A(transform.GetPosition() - glm::vec3(0, height / 2, 0)), 
		B(GetPosition() - glm::vec3(0, height / 2, 0)), radii(radii)
	{}
}