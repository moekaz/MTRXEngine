#include "PrecompiledHeader.h"
#include "ParticleManager.h"

namespace mtrx
{
	ParticleManager::ParticleManager() : collisionResolver(1)
	{}

	ParticleManager::ParticleManager(unsigned int maxContacts, unsigned int numIterations) : maxContacts(maxContacts), numIterations(numIterations),
		collisionResolver(numIterations)
	{}

	ParticleManager::~ParticleManager()
	{}

	void ParticleManager::PhysicsUpdate()
	{
		// Update the force generators
		UpdateForces();
		// Update the particles according to the accumulated forces
		UpdateParticles();
		// Update the positions according to the collisions generated
		GenerateCollisions();

		// THERE IS ALSO THE ROD AND CABLE COLLISION GENERATORS THAT WE NEED TO ADD THRIR COLLISIONS HERE

		// Resolve collisions (THIS MIGHT BE WRONG) makes some sense but not sure 
		collisionResolver.SetIterations((unsigned int)particleCollisions.size() * 2);
		collisionResolver.ResolveContacts(particleCollisions);
	}

	unsigned int ParticleManager::GenerateCollisions()
	{
		for (auto iter = particleCollisionGenerators.begin(); iter != particleCollisionGenerators.end(); ++iter)
		{
			(*iter)->GenerateContact(particleCollisions, maxContacts);
		}

		return 1;
	}

	void ParticleManager::UpdateParticles()
	{
		for (auto iter = particles.begin(); iter != particles.end(); ++iter)
		{
			//iter->PhysicsUpdate();
		}
	}

	void ParticleManager::UpdateForces()
	{
		for (auto iter = forceGenerationRegistry.begin(); iter != forceGenerationRegistry.end(); ++iter)
		{
			// Update force generators with their representative particle
			iter->registry->UpdateForceGenerators(iter->particle);
		}
	}
}