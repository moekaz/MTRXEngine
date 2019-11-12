#pragma once

#include <PrecompiledHeader.h>
#include <forceGenerators/RigidbodyGenerators/IRigidbodyForceGenerator.h>

namespace mtrx
{
	class rb_ForceGenerationRegistry
	{
	public:
		std::vector<std::shared_ptr<IRigidbodyForceGenerator>> forceGenerators;

		~rb_ForceGenerationRegistry() {}; // TBD: Should I handle deallocating force generators??

		inline void AddForceGenerator(const std::shared_ptr<IRigidbodyForceGenerator>& forceGenerator) { forceGenerators.push_back(forceGenerator); }
		inline void RemoveForceGenerator(const int index) { forceGenerators.erase(forceGenerators.begin() + index); }

		inline void RemoveForceGenerator(const std::shared_ptr<IRigidbodyForceGenerator>& forceGenerator)
		{
			for (auto iter = forceGenerators.begin(); iter != forceGenerators.end(); ++iter)
			{
				if (*iter == forceGenerator) { forceGenerators.erase(iter); break; }
			}
		}

		inline void UpdateForceGenerators(Rigidbody* rb, float deltaTime)
		{
			for (auto iter = forceGenerators.begin(); iter != forceGenerators.end(); ++iter)
			{
				(*iter)->UpdateForces(rb, deltaTime);
			}
		}
	};
}

