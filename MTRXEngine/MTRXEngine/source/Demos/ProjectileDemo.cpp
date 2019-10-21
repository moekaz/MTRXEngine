#include <PrecompiledHeader.h>
#include <../Demos/ProjectileDemo.h>

ProjectileDemo::ProjectileDemo() : Demo("PROJECTILE DEMO", 1366, 768), gravityGenerator(glm::vec3(0, -mtrx::gravity, 0)), projectileType(1)
{
	UILayer::AddUIPanel(new ProjectileDemoUI("Projectile Demo", glm::vec2(300, 200), &projectileType));
	application.camera->GetTransform().SetPosition(glm::vec3(0, 0, 20.f));
}

void ProjectileDemo::Update()
{
	// This is just a reference point in world space
	mtrx::Transform center =
	{
		glm::vec3(0, 0, 0),
		glm::angleAxis(0.f, mtrx::worldUp),
		glm::vec3(0.1f, 0.1f, 0.1f),
	};
	transformsToRender.insert(&center);
	
	while (!application.window.ShouldClose())
	{
		Demo::Update();
	}
}

void ProjectileDemo::InputCheck()
{
	if (application.inputSystem->GetKeyDown(GLFW_KEY_SPACE))
	{
		// Removing the rigidbody also removes the force generators that are linked with this force generator
		rbManager.RemoveRigidbody(&projectile);
		transformsToRender.erase(&projectile.GetTransform());

		// Setup projectile
		switch (projectileType)
		{
			case 1:
			{
				// Regular projectile
				float mass = 50.f;
				float extents[] = { 1.f, 1.f, 1.f };
				projectile = mtrx::Rigidbody(mass, false, glm::vec3(-40.f, 1.f, 0.f), glm::angleAxis(0.f, mtrx::worldUp), glm::vec3(1.f, 1.f, 1.f), mtrx::GenerateCuboidIT(mass, extents));
				projectile.AddForce(glm::vec3(60000.f, 50000.f, 0));
				rbManager.AddForceGenerator(&projectile, &gravityGenerator);
				break;
			}
			case 2:
			{
				// Light Projectile
				float mass = 0.0001f;;
				float extents[] = { 0.2f, 0.2f, 0.2f };
				projectile = mtrx::Rigidbody(mass, false, glm::vec3(-40.f, 1.f, 0.f), glm::angleAxis(0.f, mtrx::worldUp), glm::vec3(0.2f, 0.2f, 0.2f), mtrx::GenerateCuboidIT(mass, extents));
				projectile.AddForce(glm::vec3(1.f, 0.1f, 0));
				rbManager.AddForceGenerator(&projectile, &gravityGenerator);
				break;
			}
			case 3:
			{
				// Fireball
				float mass = 4.f;
				float extents[] = { 0.5f, 0.5f, 0.5f };

				projectile = mtrx::Rigidbody(mass, false, glm::vec3(-40.f, 1.f, 0.f), glm::angleAxis(0.f, mtrx::worldUp), glm::vec3(0.5f, 0.5f, 0.5f), mtrx::GenerateCuboidIT(mass, extents));
				projectile.AddForce(glm::vec3(3000.f, 200.f, 0));
				//projectile.SetAcceleration(glm::vec3(0, 100.f, 0));
				break;
			}
			case 4:
			{
				// Laser
				float mass = 0.01f;
				float extents[] = { 0.1f, 0.1f, 0.1f };
				projectile = mtrx::Rigidbody(mass, false, glm::vec3(-40.f, 1.f, 0.f), glm::angleAxis(0.f, mtrx::worldUp), glm::vec3(0.1f, 0.1f, 0.1f), mtrx::GenerateCuboidIT(mass, extents));
				projectile.AddForce(glm::vec3(100.f, 0.f, 0));
				break;
			}
		}
		
		// Add the created rigidbody to all the managers that we need to use
		rbManager.AddRigidbody(&projectile);
		transformsToRender.insert(&projectile.GetTransform());
	}

	if (application.inputSystem->GetKeyDown(GLFW_KEY_1))
	{
		projectileType = 1;
	}

	if (application.inputSystem->GetKeyDown(GLFW_KEY_2))
	{
		projectileType = 2;
	}	
	
	if (application.inputSystem->GetKeyDown(GLFW_KEY_3))
	{
		projectileType = 3;
	}

	if (application.inputSystem->GetKeyDown(GLFW_KEY_4))
	{
		projectileType = 4;
	}
}
