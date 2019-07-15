#include "PrecompiledHeader.h"
#include "forceGenerators/RigidbodyGenerators/rb_BuoyancyForceGenerator.h"

namespace mtrx
{
	rb_BuoyancyForceGenerator::rb_BuoyancyForceGenerator(float volumeDisplaced, float maxParticleDepth, float liquidHeight, float density) : 
		volumeDisplaced(volumeDisplaced), maxParticleDepth(maxParticleDepth), liquidLevel(liquidHeight), liquidDensity(density)
	{}

	rb_BuoyancyForceGenerator::~rb_BuoyancyForceGenerator()
	{}

	void rb_BuoyancyForceGenerator::UpdateForces(Rigidbody* rb)
	{
		float currentDepth = rb->GetPosition().y;
		if (currentDepth - maxParticleDepth >= liquidLevel)
			return;

		// Apply some buoyancy force
		glm::vec3 force = glm::vec3(0.f, liquidDensity * gravity, 0.f);
		glm::vec3 dimensions = rb->GetTransform()->scale;
		float volumeDisplaced = 1.f;
		centerOfBuoyancy = rb->GetPosition();
		if (currentDepth + maxParticleDepth <= liquidLevel)
		{
			// Calculate the complete volume of the rigidbody
			// Assuming a box atm 
			volumeDisplaced = dimensions.x * dimensions.y * dimensions.z * 2.f;
			std::cout << "completely submerged" << std::endl;
		}
		else
		{
			float submergedDepth = (dimensions.y / 2.f) + (liquidLevel - currentDepth);
			centerOfBuoyancy.y = liquidLevel + submergedDepth / 2;
			// Calculate the volume of the partially submerged object
			volumeDisplaced = dimensions.x * dimensions.z * submergedDepth;
			std::cout << "partially submerged : " << submergedDepth << std::endl;
		}
		
		// Add the volume displacement to the buoyant force
		force.y *= volumeDisplaced;

		// Add the resulting force on the rigidbody
		rb->AddForceAtPoint(force, centerOfBuoyancy);
	}
}