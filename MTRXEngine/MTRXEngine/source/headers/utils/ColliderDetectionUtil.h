#pragma once

namespace mtrx
{
	// Forward Declarations
	class Collider;
	class SphereCollider;
	class CapsuleCollider;
	class AABBCollider;
	class OOBBCollider;
	class ConvexShapeCollider;

	namespace ColliderDetectionUtil
	{
		bool Collide(const Collider& collider1, const Collider& collider2);
		bool SphereCollisionOptions(const SphereCollider& sphCollider, const Collider& collider);
		bool AABBCollisionOptions(const AABBCollider& aabb, const Collider& collider);
		bool OOBBCollisionOptions(const OOBBCollider& oobb, const Collider& collider);
		bool CapsuleCollisionOptions(const CapsuleCollider& capCollider, const Collider& collider);
		bool ConvexShapeCollisionOptions(const ConvexShapeCollider& convexCollider, const Collider& collider);
	}
}