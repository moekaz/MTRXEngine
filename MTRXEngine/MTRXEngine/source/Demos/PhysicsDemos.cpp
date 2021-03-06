#include <PrecompiledHeader.h>

#define DEMO 4

#if DEMO == 1
	#include <../Demos/ProjectileDemo.h>
#elif DEMO == 2
	#include <../Demos/CollisionDemo.h>
#elif DEMO == 3
	#include <../Demos/BuoyancyDemo.h>
#elif DEMO == 4
	#include <../Demos/FluidSimulationDemo.h>
#endif

#include <../Renderer/Input/InputSystem.h>
#include <../Demos/Demo.h>

int main()
{
#if _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	// Demo application that we want to run
	std::unique_ptr<Demo> app;
#if DEMO == 1
	app = std::make_unique<ProjectileDemo>();
#elif DEMO == 2
	app = std::make_unique<CollisionDemo>();
#elif DEMO == 3
	app = std::make_unique<BuoyancyDemo>();
#elif DEMO == 4
	app = std::make_unique<FluidSimulationDemo>();
#endif

	// Run application
	app->Run();

	return 0;
}
