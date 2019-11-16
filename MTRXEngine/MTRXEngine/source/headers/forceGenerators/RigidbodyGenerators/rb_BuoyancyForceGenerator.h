/*
	Author: Mohamed Kazma
	Description: A force generator that allows us to apply buoyancy forces (forces applied by water to keep something afloat also known as the archimedes force)
*/

#pragma once

#include <forceGenerators/RigidbodyGenerators/IRigidbodyForceGenerator.h>
#include <entities/Rigidbody.h>
#include <Defs.h>

namespace mtrx
{
	class rb_BuoyancyForceGenerator : public IRigidbodyForceGenerator
	{	
	public:
		float liquidDensity;
		float liquidLevel;
		float bodyHalfExtent;
		float volumeBody; // Displacement of liquid can be calculated from the body as volume submerged is volume displaced
		glm::vec3 gravitationalAcceleration; // Gravity
		glm::vec3 centerOfBuoyancy; // Center of the submerged polygon (we would need to dynamically calculate this)

		rb_BuoyancyForceGenerator(const glm::vec3& gravity, float volumeBody, float bodyHalfExtent, float liquidHeight = 0.f, float density = 1000.f);
		~rb_BuoyancyForceGenerator();

		virtual void UpdateForces(Rigidbody* rb, float deltaTime) override;
	};
}

