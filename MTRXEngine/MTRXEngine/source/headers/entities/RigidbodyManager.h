#pragma once

#include <entities/Rigidbody.h>
#include <forceGenerators/RigidbodyGenerators/rb_ForceGenerationRegistry.h>
#include <forceGenerators/RigidbodyGenerators/IRigidbodyForceGenerator.h>

namespace mtrx
{
	class RigidbodyManager
	{
	public:
		std::unordered_map<Rigidbody*, rb_ForceGenerationRegistry> rigidbodyRegistry;

		RigidbodyManager() = default;
		~RigidbodyManager();

		void Integrate(float deltaTime);
		void IntegrateRigidbodies(float deltaTime);
		void UpdateForces(float deltaTime);
	};
}
