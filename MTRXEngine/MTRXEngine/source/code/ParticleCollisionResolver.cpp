/*
	DEPRECATED
*/
#include "PrecompiledHeader.h"
#include "ParticleCollisionResolver.h"


namespace mtrx
{
	ParticleCollisionResolver::ParticleCollisionResolver(unsigned int numIterations) : numIterations(numIterations)
	{}

	ParticleCollisionResolver::~ParticleCollisionResolver()
	{}

	void ParticleCollisionResolver::ResolveContacts(std::list<ParticleCollision>& particleCollisions)
	{
		currentIterations = 0; // Reset the number of iterations for this frame
		while (currentIterations != numIterations)
		{
			// MIGHT NEED TO TEST THIS SOME MORE
			float maxSeparatingVelocity = 0.f;
			auto maxCollisionIter = particleCollisions.begin();
			for (auto iter = particleCollisions.begin(); iter != particleCollisions.end(); ++iter)
			{
				float sepVelocity = iter->CalculateSeparatingVelocity();
				if (sepVelocity < maxSeparatingVelocity)
				{
					maxSeparatingVelocity = sepVelocity;
					maxCollisionIter = iter;
				}
			}

			// Resolve the collision with the maximum separating velocity
			maxCollisionIter->Resolve();
			++currentIterations;
		}
	}
}
