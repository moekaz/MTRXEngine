#pragma once

#include <colliders/Collider.h>
#include <colliders/SphereCollider.h>
#include <colliders/BoxCollider.h>
#include <colliders/CapsuleCollider.h>

namespace mtrx
{
	class CollisionDetectionUtil
	{
	public:
		static bool Collide(const Collider& collider1, const Collider& collider2);
		static bool SphereCollisionOptions(const SphereCollider& sphCollider, const Collider& collider);
		static bool BoxCollisionOptions();
		static bool CapsuleCollisionOptions();

	private:
	};
}