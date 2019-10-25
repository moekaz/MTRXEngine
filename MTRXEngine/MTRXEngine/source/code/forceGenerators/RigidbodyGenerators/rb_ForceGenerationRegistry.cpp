#include <PrecompiledHeader.h>
#include <forceGenerators/RigidbodyGenerators/rb_ForceGenerationRegistry.h>

namespace mtrx
{
	rb_ForceGenerationRegistry::~rb_ForceGenerationRegistry()
	{
		//for (auto iter = forceGenerators.begin(); iter != forceGenerators.end(); ++iter)
		//{
		//	delete *iter;
		//}
	}

	void rb_ForceGenerationRegistry::RemoveForceGenerator(const IRigidbodyForceGenerator* forceGenerator)
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

	void rb_ForceGenerationRegistry::UpdateForceGenerators(Rigidbody* rb, float deltaTime)
	{
		for (auto iter = forceGenerators.begin(); iter != forceGenerators.end(); ++iter)
		{
			(*iter)->UpdateForces(rb, deltaTime);
		}
	}
}