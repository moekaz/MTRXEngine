/*
	Author: Mohamed Kazma
	Description: Interface that allows us to define different force patterns for different types of objects

	MOSTLY DEPRECATED
*/
#pragma once

#include <entities/Particle.h>

namespace mtrx
{
	// Forward declarations
	//class Particle;

	class IParticleForceGenerator
	{
	public:
		virtual void UpdateForces(Particle* particle) = 0;
	};
}