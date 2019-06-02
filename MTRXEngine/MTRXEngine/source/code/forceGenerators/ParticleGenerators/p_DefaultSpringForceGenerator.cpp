#include "PrecompiledHeader.h"
#include "forceGenerators/ParticleGenerators/p_DefaultSpringForceGenerator.h"

namespace mtrx
{
	p_DefaultSpringForceGenerator::p_DefaultSpringForceGenerator(Particle* secondParticle, float stiffness, float restLength) : secondParticle(secondParticle),
		spring(stiffness, restLength)
	{}

	p_DefaultSpringForceGenerator::~p_DefaultSpringForceGenerator()
	{}

	void p_DefaultSpringForceGenerator::UpdateForces(Particle* particle)
	{
		// Get the difference in position between the 2 particles on either side of the spring
		glm::vec3 generatedForce = particle->GetPosition() - secondParticle->GetPosition();
		float mag = glm::length(generatedForce);

		// Apply Hooke's law
		mag = spring.stiffness * abs(mag - spring.restLength);

		glm::normalize(generatedForce);
		generatedForce *= -mag;
		particle->AddForce(generatedForce);
	}
}
