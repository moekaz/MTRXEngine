#include <PrecompiledHeader.h>
#include <utils/ColliderDetectionUtil.h>
#include <colliders/Collider.h>
#include <colliders/SphereCollider.h>
#include <colliders/BoxCollider.h>
#include <colliders/CapsuleCollider.h>

namespace mtrx
{
	namespace ColliderDetectionUtil
	{
		bool Collide(const Collider& collider1, const Collider& collider2)
		{
			switch (collider1.GetColliderType())
			{
				case ColliderType::Sphere:
					return SphereCollisionOptions(static_cast<const SphereCollider&>(collider1), collider2);
				case ColliderType::Box:
					return BoxCollisionOptions(static_cast<const BoxCollider&>(collider1), collider2);
				case ColliderType::Capsule:
					return CapsuleCollisionOptions(static_cast<const CapsuleCollider&>(collider1), collider2);
				default: // Not a collider that we support
					return false;
			}
		}

		bool SphereCollisionOptions(const SphereCollider& sphCollider, const Collider& collider)
		{
			switch (collider.GetColliderType())
			{
				case ColliderType::Sphere:
				{
					std::cout << "sphere sphere" << std::endl;
					const SphereCollider& sphereCollider = static_cast<const SphereCollider&>(collider);
					return CollisionUtil::SphereSphereCollision(sphCollider.GetPosition(), sphereCollider.GetPosition(), sphCollider.radius, sphereCollider.radius);
				}
				case ColliderType::Box:
				{
					std::cout << "Sphere Box" << std::endl;
					const BoxCollider& boxCollider = static_cast<const BoxCollider&>(collider);
					return CollisionUtil::SphereBoxCollision(sphCollider.GetPosition(), boxCollider.GetPosition(), sphCollider.radius, boxCollider.GetAxes(), boxCollider.GetHalfExtents());
				}
				case ColliderType::Capsule:
				{
					std::cout << "sphere capsule" << std::endl;
					const CapsuleCollider& capsuleCollider = static_cast<const CapsuleCollider&>(collider);
					return CollisionUtil::SphereCapsuleCollision(sphCollider.GetPosition(), capsuleCollider.GetPosition(), sphCollider.radius, capsuleCollider.radii, capsuleCollider.A, capsuleCollider.B);
				}
				default: // Not a collider that we support
					return false;
			}
		}

		bool BoxCollisionOptions(const BoxCollider& boxCollider, const Collider& collider)
		{
			switch (collider.GetColliderType())
			{
				case ColliderType::Sphere: // Extra switch to avoid duplication TBD: maybe might need to do smthg a little better
				{
					std::cout << "box sphere" << std::endl;
					return SphereCollisionOptions(static_cast<const SphereCollider&>(collider), boxCollider);
				}
				case ColliderType::Box:
				{
					std::cout << "box box" << std::endl;
					const BoxCollider& bxCollider = static_cast<const BoxCollider&>(collider);
					std::vector<glm::vec3*>* vertices1 = boxCollider.GetVertices();
					std::vector<glm::vec3*>* vertices2 = bxCollider.GetVertices();
					return CollisionUtil::BoxBoxCollision(vertices1->begin(), vertices1->end(), vertices2->begin(), vertices2->end());
				}
				case ColliderType::Capsule:
				{
					std::cout << "box capsule" << std::endl;
					const CapsuleCollider& capsuleCollider = static_cast<const CapsuleCollider&>(collider);
					return CollisionUtil::BoxCapsuleCollision(boxCollider.GetPosition(), capsuleCollider.GetPosition(), capsuleCollider.A, capsuleCollider.B, capsuleCollider.radii, boxCollider.GetAxes(), boxCollider.GetHalfExtents());
				}
				default: // Not a collider that we support
					return false;
			}
		}

		bool CapsuleCollisionOptions(const CapsuleCollider& capCollider, const Collider& collider)
		{
			switch (collider.GetColliderType())
			{
				case ColliderType::Sphere: // Extra switch to avoid duplication TBD: maybe might need to do something a little better
				{
					std::cout << "capsule sphere" << std::endl;
					return SphereCollisionOptions(static_cast<const SphereCollider&>(collider), capCollider);
				}
				case ColliderType::Box:
				{
					std::cout << "capsule box" << std::endl;
					return BoxCollisionOptions(static_cast<const BoxCollider&>(collider), capCollider);
				}
				case ColliderType::Capsule:
				{
					std::cout << "capsule capsule" << std::endl;
					const CapsuleCollider& capsuleCollider = static_cast<const CapsuleCollider&>(collider);
					return CollisionUtil::CapsuleCapsuleCollision(capCollider.A, capCollider.B, capsuleCollider.A, capsuleCollider.B, capCollider.radii, capsuleCollider.radii);
				}
				default: // Not a collider that we support
					return false;
			}
		}
	}
}