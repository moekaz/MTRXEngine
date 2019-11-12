#pragma once

#include <entities/RigidbodyManager.h>
#include <colliders/CollisionSystem.h>

namespace mtrx
{
	class mtrxDynamicWorld
	{
	public:
		float accumulator;

		mtrxDynamicWorld();
		~mtrxDynamicWorld();

		void Update(float dt);
		
		// Rigidbody API
		// This will do the allocation for us if it doesn't exist otherwise nothing happens
		inline void AddRigidbody(Rigidbody* rb) { m_rbManager.rigidbodyRegistry[rb]; }
		inline void RemoveRigidbody(Rigidbody* rb)
		{
			m_rbManager.rigidbodyRegistry.erase(rb);
			delete rb;
		}

		// Force generator API
		inline void AddForceGenerator(Rigidbody* rb, const std::shared_ptr<IRigidbodyForceGenerator>& forceGenerator) 
		{
			m_rbManager.rigidbodyRegistry[rb].AddForceGenerator(forceGenerator); 
		}
		
		inline void RemoveForceGenerator(Rigidbody* rb, const std::shared_ptr<IRigidbodyForceGenerator> generator)
		{
			m_rbManager.rigidbodyRegistry[rb].RemoveForceGenerator(generator); 
		}

	private:
		RigidbodyManager m_rbManager;
		CollisionSystem m_CollisionSystem;

	};
}