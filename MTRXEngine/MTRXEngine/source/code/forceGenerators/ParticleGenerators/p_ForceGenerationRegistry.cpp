#include <PrecompiledHeader.h>
#include <forceGenerators/ParticleGenerators/p_ForceGenerationRegistry.h>

namespace mtrx
{
	p_ForceGenerationRegistry::p_ForceGenerationRegistry()
	{}

	p_ForceGenerationRegistry::~p_ForceGenerationRegistry()
	{}

	void p_ForceGenerationRegistry::RemoveForceGenerator(const IParticleForceGenerator* forceGenerator)
	{
		for (auto iter = forceGenerators.begin(); iter != forceGenerators.end(); ++iter)
		{
			if (*iter == forceGenerator)
			{
				forceGenerators.erase(iter);
				break;
			}
		}
	}

	void p_ForceGenerationRegistry::UpdateForceGenerators(Particle* particle)
	{
		for (auto iter = forceGenerators.begin(); iter != forceGenerators.end(); ++iter)
		{
			(*iter)->UpdateForces(particle);
		}
	}
}