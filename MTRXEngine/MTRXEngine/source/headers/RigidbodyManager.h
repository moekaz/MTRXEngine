/*
*/

#pragma once

#include <entities/Rigidbody.h>
#include <forceGenerators/RigidbodyGenerators/rb_ForceGenerationRegistry.h>
#include <IUpdateable.h>
#include <forceGenerators/RigidbodyGenerators/IRigidbodyForceGenerator.h>

namespace mtrx
{
	// Each rigidbody will hold a force registry that will update this rigidbody
	struct rbForceGenerators
	{
		Rigidbody* rb;
		rb_ForceGenerationRegistry* registry;

		rbForceGenerators(Rigidbody* rb, rb_ForceGenerationRegistry* registry) : rb(rb), registry(registry) 
		{}
	};

	class RigidbodyManager : public IUpdateable
	{
	public:
		std::unordered_map<Rigidbody*, rb_ForceGenerationRegistry> forceGenerators;
		std::list<Rigidbody*> rigidbodies;

		RigidbodyManager();
		~RigidbodyManager();

		inline void AddRigidbody(Rigidbody* rb) { rigidbodies.push_back(rb); }
		inline void AddForceGenerator(Rigidbody* rb, IRigidbodyForceGenerator* forceGenerator) { forceGenerators[rb].AddForceGenerator(forceGenerator); }
		inline void RemoveForceGenerator(Rigidbody* rb, IRigidbodyForceGenerator* generator) { forceGenerators[rb].RemoveForceGenerator(generator); }

		inline void RemoveRigidbody(Rigidbody* rb) 
		{
			rigidbodies.remove(rb); 
			forceGenerators.erase(rb);
		}

		virtual void PhysicsUpdate() override;
		void UpdateRigidbodies();
		void UpdateForces();
		void GenerateCollisions();
	};
}
