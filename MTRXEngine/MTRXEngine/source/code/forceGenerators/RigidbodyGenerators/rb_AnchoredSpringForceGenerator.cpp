#include "PrecompiledHeader.h"
#include "forceGenerators/RigidbodyGenerators/rb_AnchoredSpringForceGenerator.h"

namespace mtrx
{
	rb_AnchoredSpringForceGenerator::rb_AnchoredSpringForceGenerator(glm::vec3* anchorPoint, float stiffness, float restLength) : anchorPoint(anchorPoint),
		spring(stiffness, restLength)
	{}

	rb_AnchoredSpringForceGenerator::~rb_AnchoredSpringForceGenerator()
	{}

	void rb_AnchoredSpringForceGenerator::UpdateForces(Rigidbody* rb, float deltaTime)
	{
		// CHANGE THIS 

		// Get the difference in position between the 2 particles on either side of the spring
		glm::vec3 generatedForce = rb->GetPosition() - *anchorPoint;
		float mag = glm::length(generatedForce);

		// Apply Hooke's law
		mag = spring.stiffness * abs(mag - spring.restLength);

		glm::normalize(generatedForce);
		generatedForce *= -mag;
		rb->AddForce(generatedForce);
	}
}
