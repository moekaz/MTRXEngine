#include "PrecompiledHeader.h"
#include "forceGenerators/RigidbodyGenerators/rb_BungeeSpringForceGenerator.h"


namespace mtrx
{
	rb_BungeeSpringForceGenerator::rb_BungeeSpringForceGenerator(glm::vec3* anchorPoint, float stiffness, float restLength) :
		rb_AnchoredSpringForceGenerator(anchorPoint, stiffness, restLength)
	{}

	rb_BungeeSpringForceGenerator::~rb_BungeeSpringForceGenerator()
	{}

	void rb_BungeeSpringForceGenerator::UpdateForces(Rigidbody* rb)
	{
		// CHANGE THIS 

		// Get the difference in position between the 2 particles on either side of the spring
		glm::vec3 generatedForce = rb->GetPosition() - *anchorPoint;
		float mag = glm::length(generatedForce);

		// Check that the spring is extended since no force will be generated unless it is
		if (mag <= spring.restLength)
			return;

		// Apply Hooke's law
		mag = spring.stiffness * abs(mag - spring.restLength);

		glm::normalize(generatedForce);
		generatedForce *= -mag;
		rb->AddForce(generatedForce);
	}
}