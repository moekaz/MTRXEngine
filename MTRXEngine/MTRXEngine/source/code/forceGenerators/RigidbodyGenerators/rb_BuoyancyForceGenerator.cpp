#include "PrecompiledHeader.h"
#include "forceGenerators/RigidbodyGenerators/rb_BuoyancyForceGenerator.h"

namespace mtrx
{
	rb_BuoyancyForceGenerator::rb_BuoyancyForceGenerator(const glm::vec3& gravity, float volumeBody, float bodyHalfExtent, float liquidHeight, float density) :
		gravitationalAcceleration(gravity), volumeBody(volumeBody), bodyHalfExtent(bodyHalfExtent), liquidLevel(liquidHeight),
		liquidDensity(density)
	{}

	rb_BuoyancyForceGenerator::~rb_BuoyancyForceGenerator()
	{}

	void rb_BuoyancyForceGenerator::UpdateForces(Rigidbody* rb, float deltaTime)
	{
		// Check if the object is not submerged
		float currentDepth = rb->GetPosition().y;
		float distLiquid = currentDepth - liquidLevel;

		// TBD: If we want it to be more robust we need to find the closest point 
		// to the water level and calculate the closest level from there
		if (distLiquid >= bodyHalfExtent)
		{
			return;
		}

		distLiquid = -distLiquid; // Get the distance from the depth of the obj to the liquid plane
		glm::vec3 force = this->liquidDensity * -this->gravitationalAcceleration; // Density and gravitional acceleration
		float volumeDisplaced = this->volumeBody;
		// centerOfBuoyancy = rb->GetPosition(); // TBD: Use center of buoyancy will require more collision information

		if (distLiquid < bodyHalfExtent) // partially submerged
		{
			// TBD: This should be replaced with some collision detection information (might be replaced with polygon calculation)
			glm::vec3 bottomPt = rb->GetPosition() - glm::vec3(0, bodyHalfExtent, 0);
			float ratioDisplaced = (liquidLevel - bottomPt.y) / (2.f * bodyHalfExtent);
			volumeDisplaced = this->volumeBody * ratioDisplaced;
		}
		
		// Add the volume displacement to the buoyancy force
		force *= volumeDisplaced;
		rb->AddForceAtPoint(force, rb->GetPosition() - glm::vec3(0, bodyHalfExtent, 0));
	}
}