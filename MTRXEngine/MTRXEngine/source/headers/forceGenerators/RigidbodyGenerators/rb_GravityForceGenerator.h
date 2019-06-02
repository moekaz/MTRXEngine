/*
	Author: Mohamed Kazma
	Description: A gravity force generator that allows us to simulate gravitational forces on a particle 
*/
#pragma once

#include <forceGenerators/RigidbodyGenerators/IRigidbodyForceGenerator.h>
#include <entities/Rigidbody.h>

namespace mtrx
{
	class rb_GravityForceGenerator : public IRigidbodyForceGenerator
	{
	public:
		glm::vec3 gravitationalAcceleration; // Gravitational acceleration

		// Implementation of an update forces for a force generator will apply a gravitational force on the particle
		virtual void UpdateForces(Rigidbody* rb); 

		rb_GravityForceGenerator(const glm::vec3& gravity);
		~rb_GravityForceGenerator();
	};
}

