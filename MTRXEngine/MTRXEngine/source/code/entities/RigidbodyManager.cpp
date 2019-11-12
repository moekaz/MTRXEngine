#include <PrecompiledHeader.h>
#include <entities/RigidbodyManager.h>

namespace mtrx
{
	void RigidbodyManager::Integrate(float deltaTime)
	{	
		UpdateForces(deltaTime);
		IntegrateRigidbodies(deltaTime);
	}

	void RigidbodyManager::IntegrateRigidbodies(float deltaTime)
	{
		for (auto iter = rigidbodyRegistry.begin(); iter != rigidbodyRegistry.end(); ++iter)
		{
			iter->first->Integrate(deltaTime);
		}
	}

	void RigidbodyManager::UpdateForces(float deltaTime)
	{
		for (auto iter = rigidbodyRegistry.begin(); iter != rigidbodyRegistry.end(); ++iter)
		{
			iter->second.UpdateForceGenerators(iter->first, deltaTime);
		}
	}
}