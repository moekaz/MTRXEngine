#pragma once

#include <entities/RigidbodyManager.h>
#include <colliders/CollisionSystem.h>
#include <colliders/Collider.h>
#include <entities/Rigidbody.h>

namespace mtrx
{
	/**
	 * @brief Entry point of the user to the engine. This class defines the API that user will be using to interface with the engine
	 * 
	 */
	class mtrxDynamicWorld
	{
	public:
		float accumulator;

		/**
		 * @brief Construct a new mtrx Dynamic World object
		 * 
		 */
		mtrxDynamicWorld();

		/**
		 * @brief Destroy the mtrx Dynamic World object
		 * 
		 */
		~mtrxDynamicWorld() = default;

		/**
		 * @brief Update the game world
		 * 
		 * @param dt The time elapsed since the last frame
		 */
		void Update(float dt);
		
		/**
		 * @brief Add a rigidbody to the rigidbody manager
		 * 
		 * @param rb The rigidbody we want to add to the manager
		 */
		inline void AddRigidbody(Rigidbody* rb) { m_rbManager.rigidbodyRegistry[rb]; }
		
		/**
		 * @brief Remove a rigidbody from the rigidbody manager
		 * 
		 * @param rb The rigidbody we want to remove
		 */
		inline void RemoveRigidbody(Rigidbody* rb)
		{
			m_rbManager.rigidbodyRegistry.erase(rb);
			delete rb;
		}

		/**
		 * @brief Add a force generator to the rigidbody manager
		 * 
		 * @param rb The rigidbody we want to add the force generator to
		 * @param forceGenerator The force generator we want to add
		 */
		inline void AddForceGenerator(Rigidbody* rb, const std::shared_ptr<IRigidbodyForceGenerator>& forceGenerator) 
		{
			m_rbManager.rigidbodyRegistry[rb].AddForceGenerator(forceGenerator); 
		}
		
		/**
		 * @brief Remove a rigidbody from the rigidbody manager
		 * 
		 * @param rb The rigidbody we want to remove the rigidbody from
		 * @param generator The force generator that we want to remove
		 */
		inline void RemoveForceGenerator(Rigidbody* rb, const std::shared_ptr<IRigidbodyForceGenerator>& generator)
		{
			m_rbManager.rigidbodyRegistry[rb].RemoveForceGenerator(generator); 
		}

		/**
		 * @brief Add a collider to the collision system
		 * 
		 * @param col The collider that we want to add 
		 */
		inline void AddCollider(Collider* col) { m_CollisionSystem.colliders.insert(col); }

		/**
		 * @brief Remove a collider to the collision system
		 * 
		 * @param col The collider that we want to remove
		 */
		inline void RemoveCollider(Collider* col) 
		{
			m_CollisionSystem.colliders.erase(col); 
			delete col; 
		}

	private:
		RigidbodyManager m_rbManager;
		CollisionSystem m_CollisionSystem;

	};
}