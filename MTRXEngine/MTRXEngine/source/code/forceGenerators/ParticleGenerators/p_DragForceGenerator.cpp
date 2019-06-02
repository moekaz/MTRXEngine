#include <PrecompiledHeader.h>
#include "forceGenerators/ParticleGenerators/p_DragForceGenerator.h"

namespace mtrx
{
	p_DragForceGenerator::p_DragForceGenerator(float k1, float k2) : k1(k1), k2(k2)
	{}

	p_DragForceGenerator::~p_DragForceGenerator()
	{}

	void p_DragForceGenerator::UpdateForces(Particle* particle)
	{
		// Check for infinite mass
		if (particle->GetIsInfiniteMass())
			return;
		
		// MIGHT NEED SOME OPTIMIZATION FOR SQRT CALLS??
		glm::vec3& velocity = particle->GetVelocity();
		float dragScalar = glm::length(particle->GetVelocity());
		dragScalar = k1 * dragScalar + k2 * dragScalar * dragScalar; // Calculate drag coefficient
		
		glm::vec3 dragForce = glm::normalize(velocity); // Get the direction vector of the velocity so that drag is against it
		dragForce *= -dragScalar;

		particle->AddForce(dragForce);
	}
}
