#include "PrecompiledHeader.h"
#include "colliders/CollisionSystem.h"

namespace mtrx
{
	CollisionSystem::CollisionSystem()
	{
		//root = new BVHNode<SphereCollider>();
	}

	CollisionSystem::~CollisionSystem()
	{
		for (auto iter = colliders.begin(); iter != colliders.end(); ++iter)
		{
			Collider* col = *iter;
			if (!col)
				continue;

			delete col;
		}
	}
}