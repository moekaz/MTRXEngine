#pragma once

#include <PrecompiledHeader.h>
#include <forceGenerators/RigidbodyGenerators/IRigidbodyForceGenerator.h>

namespace mtrx
{
	class rb_ForceGenerationRegistry
	{
	public:
		rb_ForceGenerationRegistry() = default;
		~rb_ForceGenerationRegistry() {}; // TBD: Should I handle deallocating force generators??

		inline void AddForceGenerator(IRigidbodyForceGenerator* forceGenerator) { forceGenerators.push_back(forceGenerator); }
		inline void RemoveForceGenerator(const int index) { forceGenerators.erase(forceGenerators.begin() + index); }
		inline void ClearForceGenerators() { forceGenerators.clear(); }

		inline void RemoveForceGenerator(const IRigidbodyForceGenerator* forceGenerator)
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

	private:
		std::vector<IRigidbodyForceGenerator*> forceGenerators;
	};
}

