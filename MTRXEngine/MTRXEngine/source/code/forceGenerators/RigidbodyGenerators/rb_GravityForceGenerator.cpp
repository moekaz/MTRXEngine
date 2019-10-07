#include "PrecompiledHeader.h"
#include "forceGenerators/RigidbodyGenerators/rb_GravityForceGenerator.h"

namespace mtrx
{
	rb_GravityForceGenerator::rb_GravityForceGenerator(const glm::vec3& gravity) : gravitationalAcceleration(gravity)
	{}

	rb_GravityForceGenerator::~rb_GravityForceGenerator()
	{}

	void rb_GravityForceGenerator::UpdateForces(Rigidbody* rb, float deltaTime)
	{
		// Check for infinite mass
		if (rb->GetIsInfiniteMass())
			return;
		
		// Add gravitational force to the body
		rb->AddForce(gravitationalAcceleration * rb->GetMass());
	}
}