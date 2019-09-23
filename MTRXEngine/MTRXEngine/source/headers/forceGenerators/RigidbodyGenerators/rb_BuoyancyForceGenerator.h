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
		float volumeDisplaced;
		float liquidLevel;
		float maxParticleDepth;
		glm::vec3 centerOfBuoyancy;	

		rb_BuoyancyForceGenerator(float volume, float maxPaticleDepth, float liquidHeight = 0.f, float density = 1000.f);
		~rb_BuoyancyForceGenerator();

		virtual void UpdateForces(Rigidbody* rb, float deltaTime) override;
	};
}

