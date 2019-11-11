#pragma once

#include <entities/Rigidbody.h>
#include <forceGenerators/RigidbodyGenerators/rb_ForceGenerationRegistry.h>
#include <entities/IIntegratable.h>
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
		~RigidbodyManager(); // TBD: Deallocation responsibility is it ours

		virtual void Integrate(float deltaTime) override;
		void IntegrateRigidbodies(float deltaTime);
		void UpdateForces(float deltaTime);
	};
}
