#include <PrecompiledHeader.h>

#include <utils/ColliderDetectionUtil.h>
#include <colliders/Collider.h>
#include <colliders/SphereCollider.h>
#include <colliders/BoxCollider.h>
#include <colliders/CapsuleCollider.h>
#include <colliders/ConvexShapeCollider.h>

namespace mtrx
{
	namespace ColliderDetectionUtil
	{
		bool Collide(const Collider& collider1, const Collider& collider2)
		{
			// TBD: ADD THESE OPTIONS AFTER WE ADD AABBs and OOBBs
			switch (collider1.GetColliderType())
			{
				case ColliderType::Sphere:
					return SphereCollisionOptions(static_cast<const SphereCollider&>(collider1), collider2);
				case ColliderType::Box:
					return BoxCollisionOptions(static_cast<const BoxCollider&>(collider1), collider2);
				case ColliderType::Capsule:
					return CapsuleCollisionOptions(static_cast<const CapsuleCollider&>(collider1), collider2);
				case ColliderType::ConvexShape:
					return ConvexShapeCollisionOptions(static_cast<const ConvexShapeCollider&>(collider1), collider2);
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
					const SphereCollider& sphereCollider = static_cast<const SphereCollider&>(collider);
					return CollisionUtil::SphereSphereCollision(sphCollider.GetPosition(), sphereCollider.GetPosition(), sphCollider.GetRadius(), sphereCollider.GetRadius());
				}
				case ColliderType::Box:
				{
					const BoxCollider& boxCollider = static_cast<const BoxCollider&>(collider);
					return CollisionUtil::SphereBoxCollision(sphCollider.GetPosition(), boxCollider.GetPosition(), sphCollider.GetRadius(), boxCollider.GetAxes(), boxCollider.GetHalfExtents());
				}
				case ColliderType::Capsule:
				{
					const CapsuleCollider& capsuleCollider = static_cast<const CapsuleCollider&>(collider);
					return CollisionUtil::SphereCapsuleCollision(sphCollider.GetPosition(), capsuleCollider.GetPosition(), sphCollider.GetRadius(), capsuleCollider.GetRadii(), capsuleCollider.A, capsuleCollider.B);
				}
				default: // Not a collider that we support
					return false;
			}
		}

		bool BoxCollisionOptions(const BoxCollider& boxCollider, const Collider& collider)
		{
			switch (collider.GetColliderType())
			{
				case ColliderType::Sphere:
				{
					return SphereCollisionOptions(static_cast<const SphereCollider&>(collider), boxCollider);
				}
				case ColliderType::Box:
				{					const BoxCollider& bxCollider = static_cast<const BoxCollider&>(collider);
					auto vertices1 = boxCollider.GetVertices();
					auto vertices2 = bxCollider.GetVertices();
					return CollisionUtil::BoxBoxCollision(vertices1->begin(), vertices1->end(), vertices2->begin(), vertices2->end());
				}
				case ColliderType::Capsule:
				{
					const CapsuleCollider& capsuleCollider = static_cast<const CapsuleCollider&>(collider);
					return CollisionUtil::BoxCapsuleCollision(boxCollider.GetPosition(), capsuleCollider.GetPosition(), capsuleCollider.A, capsuleCollider.B, capsuleCollider.GetRadii(), boxCollider.GetAxes(), boxCollider.GetHalfExtents());
				}
				default: // Not a collider that we support
					return false;
			}
		}

		bool CapsuleCollisionOptions(const CapsuleCollider& capCollider, const Collider& collider)
		{
			switch (collider.GetColliderType())
			{
				case ColliderType::Sphere:
				{
					return SphereCollisionOptions(static_cast<const SphereCollider&>(collider), capCollider);
				}
				case ColliderType::Box:
				{
					return BoxCollisionOptions(static_cast<const BoxCollider&>(collider), capCollider);
				}
				case ColliderType::Capsule:
				{
					const CapsuleCollider& capsuleCollider = static_cast<const CapsuleCollider&>(collider);
					return CollisionUtil::CapsuleCapsuleCollision(capCollider.A, capCollider.B, capsuleCollider.A, capsuleCollider.B, capCollider.GetRadii(), capsuleCollider.GetRadii());
				}
				default: // Not a collider that we support
					return false;
			}
		}

		bool ConvexShapeCollisionOptions(const ConvexShapeCollider& convexCollider, const Collider& collider)
		{
			switch (collider.GetColliderType())
			{
				case ColliderType::Sphere: 
				{
					return false;
				}
				case ColliderType::Box:
				{
					return false;
				}
				case ColliderType::Capsule:
				{
					return false;
				}
				case ColliderType::ConvexShape
				{
					return false;
				}
				default: // Not a collider that we support
					return false;
			}
		}
	}
}