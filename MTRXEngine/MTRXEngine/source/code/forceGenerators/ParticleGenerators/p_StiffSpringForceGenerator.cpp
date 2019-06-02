#include "PrecompiledHeader.h"
#include "forceGenerators/ParticleGenerators/p_StiffSpringForceGenerator.h"

namespace mtrx
{
	p_StiffSpringForceGenerator::p_StiffSpringForceGenerator(glm::vec3* anchorPoint, float springStiffness, float springDamping) : anchorPoint(anchorPoint),
		springStiffness(springStiffness), springDamping(springDamping)
	{}

	p_StiffSpringForceGenerator::~p_StiffSpringForceGenerator()
	{}

	void p_StiffSpringForceGenerator::UpdateForces(Particle* particle)
	{
		// Check for infinite mass
		if (particle->GetIsInfiniteMass())
			return;

		// Get the vector from the anchor to the particle connected to this string
		glm::vec3 pos = particle->GetPosition();
		glm::vec3& velocity = particle->GetVelocity();
		pos -= *anchorPoint;

		// Calculate Gamma used to calculate c (Must not be zero)
		float gamma = 0.5f * sqrt(4 * springStiffness - springDamping * springDamping);
		if (gamma == 0.0f)
			return;

		// Calculate c for the differential equation that we are using
		glm::vec3 c = springDamping / (2.f * gamma) * pos + velocity * 1.f / gamma;
	
		// Apply the differential equation to calculate the position
		glm::vec3 finalPosition = (pos * cos(gamma * GameTime::deltaTime) + c * sin(gamma * GameTime::deltaTime)) * exp(-0.5f * springDamping * GameTime::deltaTime);

		// Try and get the acceleration knowing the position that it reaches 
		// IS THIS CORRECT??
		//glm::vec3 acceleration = (finalPosition - pos) * 1.f / GameTime::deltaTime * GameTime::deltaTime - velocity;
		glm::vec3 acceleration = (finalPosition - pos) * 1.f / GameTime::deltaTime * GameTime::deltaTime - velocity * GameTime::deltaTime;

		// Add the new force to the particle
		particle->AddForce(acceleration * particle->GetMass());
	}
}