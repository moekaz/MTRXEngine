#include "PrecompiledHeader.h"
#include "forceGenerators/RigidbodyGenerators/rb_StiffSpringForceGenerator.h"

namespace mtrx
{
	rb_StiffSpringForceGenerator::rb_StiffSpringForceGenerator(glm::vec3* anchorPoint, float springStiffness, float springDamping) : anchorPoint(anchorPoint),
		springStiffness(springStiffness), springDamping(springDamping)
	{}

	rb_StiffSpringForceGenerator::~rb_StiffSpringForceGenerator()
	{}

	void rb_StiffSpringForceGenerator::UpdateForces(Rigidbody* rb, float deltaTime)
	{
		// Check for infinite mass
		if (rb->GetIsInfiniteMass())
			return;

		// Get the vector from the anchor to the particle connected to this string
		glm::vec3& pos = rb->GetPosition();
		glm::vec3& velocity = rb->GetVelocity();
		pos -= *anchorPoint;

		// Calculate Gamma used to calculate c (Must not be zero)
		float gamma = 0.5f * sqrt(4 * springStiffness - springDamping * springDamping);
		if (gamma == 0.0f)
			return;

		// Calculate c for the differential equation that we are using
		glm::vec3 c = springDamping / (2.f * gamma) * pos + velocity * 1.f / gamma;
	
		// Apply the differential equation to calculate the position
		glm::vec3 finalPosition = (pos * cos(gamma * deltaTime) + c * sin(gamma * deltaTime)) * exp(-0.5f * springDamping * deltaTime);

		// Try and get the acceleration knowing the position that it reaches 
		glm::vec3 acceleration;
		if(deltaTime != 0.f)
			acceleration = (finalPosition - pos) * 1.f / deltaTime * deltaTime - velocity * deltaTime;

		// Add the new force to the particle
		rb->AddForce(acceleration * rb->GetMass());
	}
}