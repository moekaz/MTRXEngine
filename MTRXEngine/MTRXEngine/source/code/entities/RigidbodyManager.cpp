#include <PrecompiledHeader.h>
#include <entities/RigidbodyManager.h>

#define PHYSICS_TIMESTEP 0.01666666666f // 60fps timestep

namespace mtrx
{
	RigidbodyManager::RigidbodyManager() : accumulator(0)
	{}

	RigidbodyManager::~RigidbodyManager()
	{
		//for (auto iter = rigidbodies.begin(); iter != rigidbodies.end(); ++iter)
		//{
		//	delete *iter;
		//}
	}

	void RigidbodyManager::Integrate(float deltaTime)
	{
		// Update the forces of the rigidbodies
		UpdateForces(deltaTime);
		
		// Breakdown physics simulations into fixed time steps
		accumulator += deltaTime;
		while (accumulator >= PHYSICS_TIMESTEP)
		{
			IntegrateRigidbodies(PHYSICS_TIMESTEP);
			accumulator -= PHYSICS_TIMESTEP;
		}
	}

	void RigidbodyManager::IntegrateRigidbodies(float deltaTime)
	{
		for (auto iter = rigidbodies.begin(); iter != rigidbodies.end(); ++iter)
		{
			(*iter)->Integrate(deltaTime);
		}
	}

	void RigidbodyManager::UpdateForces(float deltaTime)
	{
		for (auto iter = forceGenerators.begin(); iter != forceGenerators.end(); ++iter)
		{
			iter->second.UpdateForceGenerators(iter->first, deltaTime);
		}
	}
}