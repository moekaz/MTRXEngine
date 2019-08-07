#include "PrecompiledHeader.h"
#include "RigidbodyManager.h"

namespace mtrx
{
	RigidbodyManager::RigidbodyManager()
	{}

	RigidbodyManager::~RigidbodyManager()
	{}

	void RigidbodyManager::PhysicsUpdate()
	{
		// Update the values of the rigidbodies
		UpdateRigidbodies();

		// Update the forces of the rigidbodies
		UpdateForces();
		
		// Check for collisions
		GenerateCollisions();
	}

	void RigidbodyManager::UpdateRigidbodies()
	{
		for (auto iter = rigidbodies.begin(); iter != rigidbodies.end(); ++iter)
		{
			(*iter)->PhysicsUpdate();
		}
	}

	void RigidbodyManager::UpdateForces()
	{
		for (auto iter = forceGenerators.begin(); iter != forceGenerators.end(); ++iter)
		{
			iter->second.UpdateForceGenerators(iter->first);
		}
	}

	void RigidbodyManager::GenerateCollisions()
	{}
}