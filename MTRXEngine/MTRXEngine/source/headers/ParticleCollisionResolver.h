/*
	Author: Mohamed Kazma
	Description: Resolves all particle collisions and prioritizes them according to severity of the separating velocity 
	that these collision generate ie: the lowest separating velocity (One instance of this is all we need)
*/

#pragma once

#include <ParticleCollision.h>

namespace mtrx
{
	class ParticleCollisionResolver
	{
	public:
		ParticleCollisionResolver(unsigned int numIterations);
		~ParticleCollisionResolver();

		inline void SetIterations(unsigned int iterations) { numIterations = iterations; }
		void ResolveContacts(std::list<ParticleCollision>& particleCollisions);

	private:
		unsigned int numIterations; // The number of iterations that we are going to be running at the current frame
		unsigned int currentIterations; // The number of iterations that we have currently used at the current frame
	};
}

