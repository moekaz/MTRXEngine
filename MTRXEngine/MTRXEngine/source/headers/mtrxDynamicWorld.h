#pragma once

#include <entities/RigidbodyManager.h>
#include <colliders/CollisionSystem.h>

namespace mtrx
{
	class mtrxDynamicWorld
	{
	public:
		mtrxDynamicWorld();
		~mtrxDynamicWorld();

		void Update();

	private:
		RigidbodyManager m_rbManager;
		CollisionSystem m_CollisionSystem;

	};
}