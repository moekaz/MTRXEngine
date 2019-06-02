#include "PrecompiledHeader.h"
#include "forceGenerators/ParticleGenerators/p_AnchoredSpringForceGenerator.h"

namespace mtrx
{
	p_AnchoredSpringForceGenerator::p_AnchoredSpringForceGenerator(glm::vec3* anchorPoint, float stiffness, float restLength) : anchorPoint(anchorPoint),
		spring(stiffness, restLength)
	{}

	p_AnchoredSpringForceGenerator::~p_AnchoredSpringForceGenerator()
	{}

	void p_AnchoredSpringForceGenerator::UpdateForces(Particle* particle)
	{
		// Get the difference in position between the 2 particles on either side of the spring
		glm::vec3 generatedForce = particle->GetPosition() - *anchorPoint;
		float mag = glm::length(generatedForce);

		// Apply Hooke's law
		mag = spring.stiffness * abs(mag - spring.restLength);

		glm::normalize(generatedForce);
		generatedForce *= -mag;
		particle->AddForce(generatedForce);
	}
}
