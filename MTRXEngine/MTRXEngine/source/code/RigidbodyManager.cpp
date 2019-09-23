#include "PrecompiledHeader.h"
#include "RigidbodyManager.h"

#define PHYSICS_TIMESTEP 0.01666666666f
namespace mtrx
{
	RigidbodyManager::RigidbodyManager() : accumulator(0)
	{}

	RigidbodyManager::~RigidbodyManager()
	{}

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

		// Check for collisions
		GenerateCollisions();
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

	void RigidbodyManager::GenerateCollisions()
	{}
}