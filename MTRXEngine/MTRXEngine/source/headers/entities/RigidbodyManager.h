#pragma once

#include <entities/Rigidbody.h>
#include <forceGenerators/RigidbodyGenerators/rb_ForceGenerationRegistry.h>
#include <forceGenerators/RigidbodyGenerators/IRigidbodyForceGenerator.h>

namespace mtrx
{
	class RigidbodyManager : public IIntegratable
	{
	public:
		std::unordered_map<Rigidbody*, rb_ForceGenerationRegistry> forceGenerators;
		std::list<Rigidbody*> rigidbodies;
		float accumulator;

		RigidbodyManager();
		~RigidbodyManager() = default; // TBD: Deallocation responsibility is it ours

		void Integrate(float deltaTime);
		void IntegrateRigidbodies(float deltaTime);
		void UpdateForces(float deltaTime);
	};
}
