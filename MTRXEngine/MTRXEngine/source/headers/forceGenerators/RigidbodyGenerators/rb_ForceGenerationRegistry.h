#pragma once

#include <PrecompiledHeader.h>
#include <forceGenerators/RigidbodyGenerators/IRigidbodyForceGenerator.h>

namespace mtrx
{
	/**
	 * @brief Registry for force generators used to map a rigidbody to all of the force generators that are to be applied to said rigidbody
	 * 
	 */
	class rb_ForceGenerationRegistry
	{
	public:
		std::vector<std::shared_ptr<IRigidbodyForceGenerator>> forceGenerators;

		/**
		 * @brief Construct a new rb ForceGenerationRegistry object
		 * 
		 */
		rb_ForceGenerationRegistry() = default;

		/**
		 * @brief Destroy the rb ForceGenerationRegistry object
		 * 
		 */
		~rb_ForceGenerationRegistry() = default;

		/**
		 * @brief Add a force generator to the registry
		 * 
		 * @param forceGenerator The force generator to be added
		 */
		inline void AddForceGenerator(const std::shared_ptr<IRigidbodyForceGenerator>& forceGenerator) { forceGenerators.push_back(forceGenerator); }
		
		/**
		 * @brief Remove a force generator from registry by index
		 * 
		 * @param index The position of the force generator
		 */
		inline void RemoveForceGenerator(const int index) { forceGenerators.erase(forceGenerators.begin() + index); }

		/**
		 * @brief Remove force generator
		 * 
		 * @param forceGenerator The force generator that we want to remove
		 */
		inline void RemoveForceGenerator(const std::shared_ptr<IRigidbodyForceGenerator>& forceGenerator)
		{
			for (auto iter = forceGenerators.begin(); iter != forceGenerators.end(); ++iter)
			{
				if (*iter == forceGenerator) { forceGenerators.erase(iter); break; }
			}
		}

		/**
		 * @brief Apply the force generators onto the rigidbody
		 * 
		 * @param rb The rigidbody we want to apply the forces to
		 * @param deltaTime The time elapsed from last frame
		 */
		inline void UpdateForceGenerators(Rigidbody* rb, float deltaTime)
		{
			for (auto iter = forceGenerators.begin(); iter != forceGenerators.end(); ++iter)
			{
				(*iter)->UpdateForces(rb, deltaTime);
			}
		}
	};
}

