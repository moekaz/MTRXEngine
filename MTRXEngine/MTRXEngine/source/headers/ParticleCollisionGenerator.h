/*
	Author: Mohamed Kazma
	Description: A particle collision generator interface that is used to add a particle collision to a given structure 
	and can be implemented differently in the same manner as force generators
*/

#pragma once

#include <ParticleCollision.h>

namespace mtrx
{
	class ParticleCollisionGenerator
	{
	public:
		// Add a particle collision to the list of particle collisions  
		virtual void GenerateContact(std::list<ParticleCollision>& collisions, unsigned int limit) = 0;
	};
}
