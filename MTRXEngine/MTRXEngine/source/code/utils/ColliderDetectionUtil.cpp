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
			switch (collider1.GetColliderType())
			{
				case ColliderType::Sphere:
				{
					return SphereCollisionOptions(static_cast<const SphereCollider&>(collider1), collider2);
				}
				case ColliderType::Capsule:
				{
					return CapsuleCollisionOptions(static_cast<const CapsuleCollider&>(collider1), collider2);
				}
				case ColliderType::AABB:
				{
					return AABBCollisionOptions(static_cast<const AABBCollider&>(collider1), collider2);
				}
				case ColliderType::OOBB:
				{
					return OOBBCollisionOptions(static_cast<const OOBBCollider&>(collider1), collider2);
				}
				case ColliderType::ConvexShape:
				{
					return ConvexShapeCollisionOptions(static_cast<const ConvexShapeCollider&>(collider1), collider2);
				}
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
				{
					const AABBCollider& aabb = static_cast<const AABBCollider&>(collider);
					return CollisionUtil::SphereAABBCollision(sphCollider.GetPosition(), sphCollider.GetRadius(), aabb.GetPosition(), aabb.GetHalfExtents());
				}
				case ColliderType::OOBB:
				{
					const OOBBCollider& oobb = static_cast<const OOBBCollider&>(collider);
					return CollisionUtil::SphereOOBBCollision(sphCollider.GetPosition(), sphCollider.GetRadius(), oobb.GetPosition(), oobb.GetAxes(), oobb.GetHalfExtents());
				}
				case ColliderType::ConvexShape:
				{
					auto vertices = static_cast<const ConvexShapeCollider&>(collider).GetVertices();
					return CollisionUtil::ConvexShapeSphereCollision(vertices->begin(), vertices->end(), (int)vertices->size(), sphCollider.GetPosition(), sphCollider.GetRadius());
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
				case ColliderType::Capsule:
				{
					const CapsuleCollider& capsuleCollider = static_cast<const CapsuleCollider&>(collider);
					return CollisionUtil::CapsuleCapsuleCollision(capCollider.A, capCollider.B, capsuleCollider.A, capsuleCollider.B, capCollider.GetRadii(), capsuleCollider.GetRadii());
				}
				case ColliderType::AABB:
				{
					const AABBCollider& aabb = static_cast<const AABBCollider&>(collider);
					return CollisionUtil::CapsuleAABBCollision(capCollider.A, capCollider.B, capCollider.GetRadii(), aabb.GetPosition(), aabb.GetHalfExtents()); 
				}
				case ColliderType::OOBB:
				{
					auto vertices = static_cast<const OOBBCollider&>(collider).GetVertices();
					return CollisionUtil::CapsuleOOBBCollision(capCollider.A, capCollider.B, capCollider.GetRadii(), vertices->begin(), vertices->end(), (int)vertices->size());
				}
				case ColliderType::ConvexShape:
				{
					auto vertices = static_cast<const ConvexShapeCollider&>(collider).GetVertices();
					return CollisionUtil::ConvexShapeCapsuleCollision(vertices->begin(), vertices->end(), (int)vertices->size(), capCollider.A, capCollider.B, capCollider.GetRadii());
				}
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
					return SphereCollisionOptions(static_cast<const SphereCollider&>(collider), aabb);
				}
				case ColliderType::Capsule:
				{
					return CapsuleCollisionOptions(static_cast<const CapsuleCollider&>(collider), aabb);
				}
				case ColliderType::AABB:
				{
					const AABBCollider& aabb1 = static_cast<const AABBCollider&>(collider);
					return CollisionUtil::AABBCollision(aabb.GetPosition(), aabb.GetHalfExtents(), aabb1.GetPosition(), aabb1.GetHalfExtents());
				}
				case ColliderType::OOBB:
				{
					auto vertices = aabb.GetVertices();
					auto vertices1 = static_cast<const OOBBCollider&>(collider).GetVertices();
					return CollisionUtil::AABBOOBBCollision(vertices->begin(), vertices->end(), vertices1->begin(), vertices1->end());
				}
				case ColliderType::ConvexShape:
				{
					auto vertices = aabb.GetVertices();
					auto vertices1 = static_cast<const ConvexShapeCollider&>(collider).GetVertices();
					return CollisionUtil::ConvexShapeCollision(vertices->begin(), vertices->end(), vertices1->begin(), vertices1->end());
				}
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
					return SphereCollisionOptions(static_cast<const SphereCollider&>(collider), oobb);
				}
				case ColliderType::Capsule:
				{
					return CapsuleCollisionOptions(static_cast<const CapsuleCollider&>(collider), oobb);
				}
				case ColliderType::AABB:
				{
					return AABBCollisionOptions(static_cast<const AABBCollider&>(collider), oobb);
				}
				case ColliderType::OOBB:
				{
					auto vertices = oobb.GetVertices();
					auto vertices1 = static_cast<const OOBBCollider&>(collider).GetVertices();
					return CollisionUtil::OOBBCollision(vertices->begin(), vertices->end(), vertices1->begin(), vertices1->end());
				}
				case ColliderType::ConvexShape:
				{
					auto vertices = oobb.GetVertices();
					auto vertices1 = static_cast<const ConvexShapeCollider&>(collider).GetVertices();
					return CollisionUtil::ConvexShapeCollision(vertices->begin(), vertices->end(), vertices1->begin(), vertices1->end());
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
					return SphereCollisionOptions(static_cast<const SphereCollider&>(collider), convexCollider);
				}
				case ColliderType::Capsule:
				{
					return CapsuleCollisionOptions(static_cast<const CapsuleCollider&>(collider), convexCollider);
				}
				case ColliderType::AABB:
				{
					return AABBCollisionOptions(static_cast<const AABBCollider&>(collider), convexCollider);
				}
				case ColliderType::OOBB:
				{
					return OOBBCollisionOptions(static_cast<const OOBBCollider&>(collider), convexCollider);
				}
				case ColliderType::ConvexShape:
				{
					auto vertices = convexCollider.GetVertices();
					auto vertices1 = convexCollider.GetVertices();
					return CollisionUtil::ConvexShapeCollision(vertices->begin(), vertices->end(), vertices1->begin(), vertices1->end());
				}
				default: // Not a collider that we support
					return false;
			}
		}
	}
}