#include "PrecompiledHeader.h"
#include "forceGenerators/RigidbodyGenerators/rb_GravityForceGenerator.h"

namespace mtrx
{
	rb_GravityForceGenerator::rb_GravityForceGenerator(const glm::vec3& gravity) : gravitationalAcceleration(gravity)
	{}

	rb_GravityForceGenerator::~rb_GravityForceGenerator()
	{}

	void rb_GravityForceGenerator::UpdateForces(Rigidbody* particle)
	{
		// Check for infinite mass
		if (particle->GetIsInfiniteMass())
			return;
		
		// Add gravitational force to the particle according to f = ma
		particle->AddForce(gravitationalAcceleration * particle->GetMass()); 
	}
}