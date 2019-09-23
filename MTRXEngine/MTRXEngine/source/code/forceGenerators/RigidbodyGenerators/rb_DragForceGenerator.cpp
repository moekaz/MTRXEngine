#include <PrecompiledHeader.h>
#include "forceGenerators/RigidbodyGenerators/rb_DragForceGenerator.h"

namespace mtrx
{
	rb_DragForceGenerator::rb_DragForceGenerator(float k1, float k2) : k1(k1), k2(k2)
	{}

	rb_DragForceGenerator::~rb_DragForceGenerator()
	{}

	void rb_DragForceGenerator::UpdateForces(Rigidbody* rb, float deltaTime)
	{
		// REDO DIS

		// Check for infinite mass
		if (rb->GetIsInfiniteMass())
			return;
		
		// MIGHT NEED SOME OPTIMIZATION FOR SQRT CALLS??
		glm::vec3& velocity = rb->GetVelocity();
		float dragScalar = glm::length(rb->GetVelocity());
		dragScalar = k1 * dragScalar + k2 * dragScalar * dragScalar; // Calculate drag coefficient
		
		glm::vec3 dragForce = glm::normalize(velocity); // Get the direction vector of the velocity so that drag is against it
		dragForce *= -dragScalar;

		rb->AddForce(dragForce);
	}
}
