#pragma once

#include <entities/Rigidbody.h>
#include <forceGenerators/RigidbodyGenerators/rb_ForceGenerationRegistry.h>
#include <forceGenerators/RigidbodyGenerators/IRigidbodyForceGenerator.h>

namespace mtrx
{
	/**
	 * @brief Manager of rigidbodies 
	 * 
	 */
	class RigidbodyManager
	{
	public:
		std::unordered_map<Rigidbody*, rb_ForceGenerationRegistry> rigidbodyRegistry;

		/**
		 * @brief Construct a new Rigidbody Manager object
		 * 
		 */
		RigidbodyManager() = default;

		/**
		 * @brief Destroy the Rigidbody Manager object
		 * 
		 */
		~RigidbodyManager();

		/**
		 * @brief Integrate all entities of the game world
		 * 
		 * @param deltaTime The time elapsed between frames
		 */
		void Integrate(float deltaTime);
		
		/**
		 * @brief Integrate rigidbodies
		 * 
		 * @param deltaTime The time elapsed between frames
		 */
		void IntegrateRigidbodies(float deltaTime);
		
		/**
		 * @brief Update the forces applied to the rigidbodies by updating the force generators
		 * 
		 * @param deltaTime The time elapsed between frames
		 */
		void UpdateForces(float deltaTime);
	};
}
