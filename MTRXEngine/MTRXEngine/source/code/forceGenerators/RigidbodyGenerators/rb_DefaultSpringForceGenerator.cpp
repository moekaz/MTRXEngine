#include "PrecompiledHeader.h"
#include "forceGenerators/RigidbodyGenerators/rb_DefaultSpringForceGenerator.h"

namespace mtrx
{
	rb_DefaultSpringForceGenerator::rb_DefaultSpringForceGenerator(Rigidbody* secondParticle, float stiffness, float restLength) : secondParticle(secondParticle),
		spring(stiffness, restLength)
	{}

	rb_DefaultSpringForceGenerator::~rb_DefaultSpringForceGenerator()
	{}

	void rb_DefaultSpringForceGenerator::UpdateForces(Rigidbody* rb)
	{
		// REDO DIS 

		// Get the difference in position between the 2 particles on either side of the spring
		glm::vec3 generatedForce = rb->GetPosition() - secondParticle->GetPosition();
		float mag = glm::length(generatedForce);

		// Apply Hooke's law
		mag = spring.stiffness * abs(mag - spring.restLength);

		glm::normalize(generatedForce);
		generatedForce *= -mag;
		rb->AddForce(generatedForce);
	}
}
