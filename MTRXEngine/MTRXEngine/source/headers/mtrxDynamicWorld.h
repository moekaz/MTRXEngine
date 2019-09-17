#pragma once

#include <RigidbodyManager.h>
#include <ParticleManager.h>

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
		ParticleManager m_pManager;
	};
}