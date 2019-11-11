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
		// TBD: Figure out allocation and deallocation of memory responsibilities
		inline void AddRigidbody(Rigidbody* rb) { m_rbManager.rigidbodies.push_back(rb); }
		inline void RemoveRigidbody(Rigidbody* rb)
		{
			m_rbManager.rigidbodies.remove(rb);
			m_rbManager.forceGenerators.erase(rb);

			// Not sure I should be doing this
			//delete rb;
		}

		// Force generator API
		inline void AddForceGenerator(Rigidbody* rb, IRigidbodyForceGenerator* forceGenerator) { m_rbManager.forceGenerators[rb].AddForceGenerator(forceGenerator); }
		inline void RemoveForceGenerator(Rigidbody* rb, IRigidbodyForceGenerator* generator) { m_rbManager.forceGenerators[rb].RemoveForceGenerator(generator); }

	private:
		RigidbodyManager m_rbManager;
		CollisionSystem m_CollisionSystem;

	};
}