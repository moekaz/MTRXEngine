#pragma once

#include <entities/Rigidbody.h>
#include <forceGenerators/RigidbodyGenerators/rb_ForceGenerationRegistry.h>
#include <entities/IIntegratable.h>
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

	class RigidbodyManager : public IIntegratable
	{
	public:
		std::unordered_map<Rigidbody*, rb_ForceGenerationRegistry> forceGenerators;
		std::list<Rigidbody*> rigidbodies;
		float accumulator;

		RigidbodyManager();
		~RigidbodyManager() = default; // TBD: Deallocation responsibility is it ours?

		inline void AddRigidbody(Rigidbody* rb) { rigidbodies.push_back(rb); }
		inline void AddForceGenerator(Rigidbody* rb, IRigidbodyForceGenerator* forceGenerator) { forceGenerators[rb].AddForceGenerator(forceGenerator); }
		inline void RemoveForceGenerator(Rigidbody* rb, IRigidbodyForceGenerator* generator) { forceGenerators[rb].RemoveForceGenerator(generator); }
		inline void RemoveRigidbody(Rigidbody* rb) 
		{
			rigidbodies.remove(rb); 
			forceGenerators.erase(rb);
		}

		virtual void Integrate(float deltaTime) override;
		void IntegrateRigidbodies(float deltaTime);
		void UpdateForces(float deltaTime);
		void GenerateCollisions();
	};
}
