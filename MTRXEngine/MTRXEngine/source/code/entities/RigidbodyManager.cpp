#include <PrecompiledHeader.h>
#include <entities/RigidbodyManager.h>

namespace mtrx
{
	RigidbodyManager::RigidbodyManager() : accumulator(0.f)
	{}

	void RigidbodyManager::Integrate(float deltaTime)
	{	
		// Update the forces of the rigidbodies
		UpdateForces(deltaTime);
		IntegrateRigidbodies(deltaTime);
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