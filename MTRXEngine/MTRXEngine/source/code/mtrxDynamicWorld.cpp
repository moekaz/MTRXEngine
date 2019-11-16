#include <PrecompiledHeader.h>
#include <mtrxDynamicWorld.h>

namespace mtrx
{
	mtrxDynamicWorld::mtrxDynamicWorld() : accumulator(0.f)
	{}

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