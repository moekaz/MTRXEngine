#include <PrecompiledHeader.h>
#include <mtrxDynamicWorld.h>

namespace mtrx
{
	mtrxDynamicWorld::mtrxDynamicWorld() : accumulator(0.f)
	{}

	mtrxDynamicWorld::~mtrxDynamicWorld()
	{
		for (auto iter = m_rbManager.rigidbodyRegistry.begin(); iter != m_rbManager.rigidbodyRegistry.end(); ++iter)
		{
			Rigidbody* rb = iter->first;
			if (!rb)
				continue;

			delete rb;
		}
	}

	void mtrxDynamicWorld::Update(float dt)
	{
		GameTime::Update();	// Update deltaTime

		accumulator += dt; 
		while (accumulator >= PHYSICS_TIMESTEP)
		{
			// Update the rigidbody manager
			m_rbManager.Integrate(PHYSICS_TIMESTEP);
			accumulator -= PHYSICS_TIMESTEP;
		}
	}
}