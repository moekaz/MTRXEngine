#include <PrecompiledHeader.h>
#include <utils/CollisionDetectionUtil.h>

namespace mtrx
{
	bool CollisionDetectionUtil::Collide(const Collider& collider1, const Collider& collider2)
	{
		return false;
	}

	bool CollisionDetectionUtil::SphereCollisionOptions(const SphereCollider& sphCollider, const Collider& collider)
	{
		return false;
	}

	bool CollisionDetectionUtil::BoxCollisionOptions()
	{
		return false;
	}

	bool CollisionDetectionUtil::CapsuleCollisionOptions()
	{
		return false;
	}
} // namespace mtrx