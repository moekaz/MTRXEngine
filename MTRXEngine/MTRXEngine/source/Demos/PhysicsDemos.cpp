#include <PrecompiledHeader.h>

#define DEMO 3

#if DEMO == 1
	#include <../Demos/ProjectileDemo.h>
#elif DEMO == 2
	#include <../Demos/CollisionDemo.h>
#elif DEMO == 3
	#include <../Demos/BuoyancyDemo.h>
#endif

#include <log/LogManager.h>
#include <../Renderer/Input/InputSystem.h>
#include <../Demos/Demo.h>

int main()
{
	// Demo application that we want to run
	std::unique_ptr<Demo> app;
#if DEMO == 1
	app = std::make_unique<ProjectileDemo>();
#elif DEMO == 2
	app = std::make_unique<CollisionDemo>();
#elif DEMO == 3
	app = std::make_unique<BuoyancyDemo>();
#endif

	// Run application
	app->Run();

	return 0;
}
