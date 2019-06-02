/*
	Author: Mohamed Kazma
	Description: Implementation of a particle coupling that uses a cable to couple the 2 particles
*/

#pragma once

#include <ParticleCoupling.h>

namespace mtrx
{
	class ParticleCableCoupling : public ParticleCoupling
	{
	public:
		float maxLengthSqr; // The square of the max length of the cable used to check for generating a contact
		float restitution; // The bounciness of the cable

		ParticleCableCoupling(float maxLengthSqr, float restitution);
		~ParticleCableCoupling();

		virtual void GenerateContact(std::list<ParticleCollision>& collisions, unsigned int limit);
	};
}
