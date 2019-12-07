/*
	Author: Mohamed Kazma
	Description: A gravity force generator that allows us to simulate gravitational forces on a particle 
*/
#pragma once

#include <forceGenerators/RigidbodyGenerators/IRigidbodyForceGenerator.h>
#include <entities/Rigidbody.h>

namespace mtrx
{
	/**
	 * @brief Implementation of gravitational force generator
	 * 
	 */
	class rb_GravityForceGenerator : public IRigidbodyForceGenerator
	{
	public:
		glm::vec3 gravitationalAcceleration; // Gravitational acceleration

		// Implementation of an update forces for a force generator will apply a gravitational force on the particle
		
		/**
		 * @brief Implementation of the force generator
		 * 
		 * @param rb The rigidbody to apply the force onto
		 * @param deltaTime The time elapsed since the last frame
		 */
		virtual void UpdateForces(Rigidbody* rb, float deltaTime); 

		/**
		 * @brief Construct a new rb GravityForceGenerator object
		 * 
		 * @param gravity The gravitational acceleration value that we want to use
		 */
		rb_GravityForceGenerator(const glm::vec3& gravity);
		
		/**
		 * @brief Destroy the rb GravityForceGenerator object
		 * 
		 */
		~rb_GravityForceGenerator();
	};
}

