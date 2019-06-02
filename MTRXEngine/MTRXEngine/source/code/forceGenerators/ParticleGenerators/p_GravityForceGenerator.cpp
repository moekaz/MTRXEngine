#include "PrecompiledHeader.h"
#include "forceGenerators/ParticleGenerators/p_GravityForceGenerator.h"

namespace mtrx
{
	p_GravityForceGenerator::p_GravityForceGenerator(const glm::vec3& gravity) : gravitationalAcceleration(gravity)
	{}

	p_GravityForceGenerator::~p_GravityForceGenerator()
	{}

	void p_GravityForceGenerator::UpdateForces(Particle* particle)
	{
		// Check for infinite mass
		if (particle->GetIsInfiniteMass())
			return;
		
		// Add gravitational force to the particle according to f = ma
		particle->AddForce(gravitationalAcceleration * particle->GetMass()); 
	}
}