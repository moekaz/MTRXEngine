/*
	Author: Mohamed Kazma
	Description: A gravity force generator that allows us to simulate gravitational forces on a particle 
*/
#pragma once

#include <entities/Particle.h>
#include <forceGenerators/ParticleGenerators/IParticleForceGenerator.h>

namespace mtrx
{
	class p_GravityForceGenerator : public IParticleForceGenerator
	{
	public:
		glm::vec3 gravitationalAcceleration; // Gravitational acceleration

		// Implementation of an update forces for a force generator will apply a gravitational force on the particle
		virtual void UpdateForces(Particle* particle) override; 

		p_GravityForceGenerator(const glm::vec3& gravity);
		~p_GravityForceGenerator();
	};
}

