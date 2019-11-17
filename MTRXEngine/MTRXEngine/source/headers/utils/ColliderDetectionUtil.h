#pragma once

namespace mtrx
{
	// Forward Declarations
	class Collider;
	class SphereCollider;
	class BoxCollider;
	class CapsuleCollider;
	class ConvexShapeCollider;

	namespace ColliderDetectionUtil
	{
		bool Collide(const Collider& collider1, const Collider& collider2);
		bool SphereCollisionOptions(const SphereCollider& sphCollider, const Collider& collider);
		bool BoxCollisionOptions(const BoxCollider& boxCollider, const Collider& collider);
		bool CapsuleCollisionOptions(const CapsuleCollider& capCollider, const Collider& collider);
		bool ConvexShapeCollisionOptions(const ConvexShapeCollider& convexCollider, const Collider& collider);
	}
}