#include <PrecompiledHeader.h>

#include <utils/ColliderDetectionUtil.h>
#include <colliders/Collider.h>
#include <colliders/SphereCollider.h>
#include <colliders/AABBCollider.h>
#include <colliders/OOBBCollider.h>
#include <colliders/CapsuleCollider.h>
#include <colliders/ConvexShapeCollider.h>

namespace mtrx
{
	namespace ColliderDetectionUtil
	{
		bool Collide(const Collider& collider1, const Collider& collider2)
		{
			// TBD: FIX THESE OPTIONS AFTER WE ADD AABBs and OOBBs
			switch (collider1.GetColliderType())
			{
				case ColliderType::Sphere:
					return SphereCollisionOptions(static_cast<const SphereCollider&>(collider1), collider2);
				case ColliderType::Capsule:
					return CapsuleCollisionOptions(static_cast<const CapsuleCollider&>(collider1), collider2);
				case ColliderType::AABB:
					//return BoxCollisionOptions(static_cast<const BoxCollider&>(collider1), collider2);
				case ColliderType::OOBB:
					//return BoxCollisionOptions(static_cast<const BoxCollider&>(collider1), collider2);
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
				case ColliderType::Capsule:
				{
					const CapsuleCollider& capsuleCollider = static_cast<const CapsuleCollider&>(collider);
					return CollisionUtil::SphereCapsuleCollision(sphCollider.GetPosition(), capsuleCollider.GetPosition(), sphCollider.GetRadius(), capsuleCollider.GetRadii(), capsuleCollider.A, capsuleCollider.B);
				}
				case ColliderType::AABB:
					//return BoxCollisionOptions(static_cast<const BoxCollider&>(collider1), collider2);
				case ColliderType::OOBB:
					//return BoxCollisionOptions(static_cast<const BoxCollider&>(collider1), collider2);
				case ColliderType::ConvexShape:
					//return ConvexShapeCollisionOptions(static_cast<const ConvexShapeCollider&>(collider1), collider2);
				default: // Not a collider that we support
					return false;
			}
		}

		bool AABBCollisionOptions(const AABBCollider& aabb, const Collider& collider)
		{
			switch (collider.GetColliderType())
			{
				case ColliderType::Sphere:
				{
					//return SphereCollisionOptions(static_cast<const SphereCollider&>(collider), capCollider);
				}
				case ColliderType::Capsule:
				{
					//const CapsuleCollider& capsuleCollider = static_cast<const CapsuleCollider&>(collider);
					//return CollisionUtil::CapsuleCapsuleCollision(capCollider.A, capCollider.B, capsuleCollider.A, capsuleCollider.B, capCollider.GetRadii(), capsuleCollider.GetRadii());
				}
				case ColliderType::AABB:
					//return BoxCollisionOptions(static_cast<const BoxCollider&>(collider1), collider2);
				case ColliderType::OOBB:
					//return BoxCollisionOptions(static_cast<const BoxCollider&>(collider1), collider2);
				case ColliderType::ConvexShape:
					//return ConvexShapeCollisionOptions(static_cast<const ConvexShapeCollider&>(collider1), collider2);
				default: // Not a collider that we support
					return false;
			}
		}

		bool OOBBCollisionOptions(const OOBBCollider& oobb, const Collider& collider)
		{
			switch (collider.GetColliderType())
			{
				case ColliderType::Sphere:
				{
					//return SphereCollisionOptions(static_cast<const SphereCollider&>(collider), capCollider);
				}
				case ColliderType::Capsule:
				{
					//const CapsuleCollider& capsuleCollider = static_cast<const CapsuleCollider&>(collider);
					//return CollisionUtil::CapsuleCapsuleCollision(capCollider.A, capCollider.B, capsuleCollider.A, capsuleCollider.B, capCollider.GetRadii(), capsuleCollider.GetRadii());
				}
				case ColliderType::AABB:
					//return BoxCollisionOptions(static_cast<const BoxCollider&>(collider1), collider2);
				case ColliderType::OOBB:
					//return BoxCollisionOptions(static_cast<const BoxCollider&>(collider1), collider2);
				case ColliderType::ConvexShape:
					//return ConvexShapeCollisionOptions(static_cast<const ConvexShapeCollider&>(collider1), collider2);
				default: // Not a collider that we support
					return false;
			}
		}

		//bool BoxCollisionOptions(const BoxCollider& boxCollider, const Collider& collider)
		//{
		//	switch (collider.GetColliderType())
		//	{
		//		case ColliderType::Sphere:
		//		{
		//			return SphereCollisionOptions(static_cast<const SphereCollider&>(collider), boxCollider);
		//		}
		//		case ColliderType::Box:
		//		{					const BoxCollider& bxCollider = static_cast<const BoxCollider&>(collider);
		//			auto vertices1 = boxCollider.GetVertices();
		//			auto vertices2 = bxCollider.GetVertices();
		//			return CollisionUtil::BoxBoxCollision(vertices1->begin(), vertices1->end(), vertices2->begin(), vertices2->end());
		//		}
		//		case ColliderType::Capsule:
		//		{
		//			const CapsuleCollider& capsuleCollider = static_cast<const CapsuleCollider&>(collider);
		//			return CollisionUtil::BoxCapsuleCollision(boxCollider.GetPosition(), capsuleCollider.GetPosition(), capsuleCollider.A, capsuleCollider.B, capsuleCollider.GetRadii(), boxCollider.GetAxes(), boxCollider.GetHalfExtents());
		//		}
		//		default: // Not a collider that we support
		//			return false;
		//	}
		//}

		bool CapsuleCollisionOptions(const CapsuleCollider& capCollider, const Collider& collider)
		{
			switch (collider.GetColliderType())
			{
				case ColliderType::Sphere:
				{
					return SphereCollisionOptions(static_cast<const SphereCollider&>(collider), capCollider);
				}
				case ColliderType::Capsule:
				{
					const CapsuleCollider& capsuleCollider = static_cast<const CapsuleCollider&>(collider);
					return CollisionUtil::CapsuleCapsuleCollision(capCollider.A, capCollider.B, capsuleCollider.A, capsuleCollider.B, capCollider.GetRadii(), capsuleCollider.GetRadii());
				}
				case ColliderType::AABB:
					//return BoxCollisionOptions(static_cast<const BoxCollider&>(collider1), collider2);
				case ColliderType::OOBB:
					//return BoxCollisionOptions(static_cast<const BoxCollider&>(collider1), collider2);
				case ColliderType::ConvexShape:
					//return ConvexShapeCollisionOptions(static_cast<const ConvexShapeCollider&>(collider1), collider2);
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
					auto vertices = convexCollider.GetVertices();
					const SphereCollider& sphCollider = static_cast<const SphereCollider&>(collider);
					//return CollisionUtil::ConvexShapeSphereCollision(vertices->begin(), vertices->end(), vertices->size(), sphCollider.GetPosition(), sphCollider.GetRadius());
				}
				case ColliderType::Capsule:
				{
					auto vertices = convexCollider.GetVertices();
					const CapsuleCollider& capCollider = static_cast<const CapsuleCollider&>(collider);
					//return CollisionUtil::ConvexShapeCapsuleCollision(vertices->begin, vertices->end(), vertices->size(), capCollider.A, capCollider.B);
				}
				case ColliderType::AABB:
				{
					auto vertices = convexCollider.GetVertices();
					auto vertices1 = static_cast<const AABBCollider&>(collider).GetVertices();
					//return CollisionUtil::ConvexShapeCollision(vertices->begin(), vertices->end(), vertices1->begin(), vertices1->end());
				}
				case ColliderType::OOBB:
				{
					auto vertices = convexCollider.GetVertices();
					auto vertices1 = static_cast<const OOBBCollider&>(collider).GetVertices();
					//return CollisionUtil::ConvexShapeCollision(vertices->begin(), vertices->end(), vertices1->begin(), vertices1->end());
				}
				case ColliderType::ConvexShape:
				{
					auto vertices = convexCollider.GetVertices();
					auto vertices1 = static_cast<const ConvexShapeCollider&>(collider).GetVertices();
					return CollisionUtil::ConvexShapeCollision(vertices->begin(), vertices->end(), vertices1->begin(), vertices1->end());
				}
				default: // Not a collider that we support
					return false;
			}
		}
	}
}