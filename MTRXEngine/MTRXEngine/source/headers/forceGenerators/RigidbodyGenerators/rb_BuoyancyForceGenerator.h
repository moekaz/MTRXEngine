#pragma once

#include <forceGenerators/RigidbodyGenerators/IRigidbodyForceGenerator.h>
#include <entities/Rigidbody.h>
#include <Defs.h>

namespace mtrx
{
	/**
	 * @brief Implementation of a buoyancy force generator for rigidbodies 
	 * 		
	 * This force generator generally assumes that the objects behaves more like a AABB
	 * We do not calculate the point of collision with the liquid plane and how much of the object is submerged
	 * if it is not perpendicular to the liquid plane
	 */
	class rb_BuoyancyForceGenerator : public IRigidbodyForceGenerator
	{	
	public:
		float liquidDensity;
		float liquidLevel;
		float bodyHalfExtent;
		float volumeBody; // Displacement of liquid can be calculated from the body as volume submerged is volume displaced
		glm::vec3 gravitationalAcceleration; // Gravity
		glm::vec3 centerOfBuoyancy; // Center of the submerged polygon (we would need to dynamically calculate this)

		/**
		 * @brief Construct a new rb BuoyancyForceGenerator object
		 * 
		 * @param gravity The gravitational acceleration used by the generator
		 * @param volumeBody The volume of the body 
		 * @param bodyHalfExtent The half extent of the body
		 * @param liquidHeight The height of the liquid that would represent the liquid's plane
		 * @param density The density of the liquid
		 */
		rb_BuoyancyForceGenerator(const glm::vec3& gravity, float volumeBody, float bodyHalfExtent, float liquidHeight = 0.f, float density = 1000.f);
		
		/**
		 * @brief Destroy the rb BuoyancyForceGenerator object
		 * 
		 */
		~rb_BuoyancyForceGenerator();

		/**
		 * @brief The implementation of the buoyancy force
		 * 
		 * @param rb The rigidbody to apply the buoyancy force
		 * @param deltaTime The time elapsed since the last frame
		 */
		virtual void UpdateForces(Rigidbody* rb, float deltaTime) override;
	};
}

