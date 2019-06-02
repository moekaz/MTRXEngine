/*
	Author: Mohamed Kazma
	Description: Couples to particles as if connected by a cable or link and forces them to remain close to each 
	This can be done using something like particle contacts when the link or cable is taut and this will create an
	impulse which will move them back together
*/

#pragma once

#include <entities/Particle.h>
#include <ParticleCollision.h>
#include <ParticleCollisionGenerator.h>

namespace mtrx
{
	class ParticleCoupling : public ParticleCollisionGenerator
	{
	public:
		Particle* particles[2]; // The 2 particles to be coupled

		ParticleCoupling();
		~ParticleCoupling();

		// Gives us the length of the cable/ rod that connects the particles squared
		inline float GetCurrentLengthSqr() const { return glm::length2(particles[0]->GetPosition() - particles[1]->GetPosition()); }
		virtual void GenerateContact(std::list<ParticleCollision>& collisions, unsigned int limit) = 0;
	};
}
