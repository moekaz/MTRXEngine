#pragma once

#include <ParticleCoupling.h>

namespace mtrx
{
	class ParticleRodCoupling : public ParticleCoupling
	{
	public:
		float lengthSqr; // Length of the rod

		ParticleRodCoupling(float lengthSqr);
		~ParticleRodCoupling();

		// Implementation of the generation of a contact with a rod
		virtual void GenerateContact(std::list<ParticleCollision>& collisions, unsigned int limit);
	};
}
