#include <PrecompiledHeader.h>
#include <../Demos/CollisionDemo.h> 

CollisionDemo::CollisionDemo() : Demo("COLLISION DEMO", 1366, 768)
{
	application.inputSystem->ToggleCursor();

	srand((unsigned int)time(0)); // Seed for random

	// Create game obstacles  
	int numObstacles = 20;
	for (int i = 0; i < numObstacles; ++i)
	{
		float extents[3] = { 1, 1, 1 };
		float mass = 2.f;
		glm::quat orientation1 = glm::angleAxis(0.f, mtrx::worldUp);
		
		float x = (float) mtrx::RandomInt(-30, 30);
		float y = (float) mtrx::RandomInt(-30, 30);
		float z = (float) mtrx::RandomInt(-30, 30);

		mtrx::Rigidbody* body = new mtrx::Rigidbody(mass, false, glm::vec3(x, y, z), orientation1, glm::vec3(extents[0], extents[1], extents[2]), mtrx::GenerateCuboidIT(mass, extents));
		
		// Check every type of collider
		mtrx::Collider* collider = new mtrx::BoxCollider(body->GetPosition());
		
		body->SetAngularDamping(0.8f);
		body->SetLinearDamping(0.99f);

		worldRbs.push_back(body);
		worldColliders.push_back(collider);
		world.AddRigidbody(body);
		transformsToRender.insert(&body->GetTransform());
	}
}

CollisionDemo::~CollisionDemo()
{
	// TBD: DO THIS IN A COLLISION SYSTEM INSTEAD OF HERE
	for (int i = 0; i < bulletColliders.size(); ++i)
	{
		delete bulletColliders[i];
	}

	for (int i = 0; i < worldColliders.size(); ++i)
	{
		delete worldColliders[i];
	}
}

void CollisionDemo::Update()
{
	// Create the UI 
	//CollisionDemoUI ui = CollisionDemoUI("Collision Demo", glm::vec2(300, 300));
	//UILayer::AddUIPanel(&ui);

	while (!application.window.ShouldClose())
	{
		// Update colliders
		for (int i = 0; i < bulletRbs.size(); ++i)
		{
			bulletColliders[i]->SetPosition(bulletRbs[i]->GetPosition());
			bulletColliders[i]->SetOrientation(bulletRbs[i]->GetOrientation());
		}

		for (int i = 0; i < worldRbs.size(); ++i)
		{
			worldColliders[i]->SetPosition(worldRbs[i]->GetPosition());
			worldColliders[i]->SetOrientation(worldRbs[i]->GetOrientation());
		}

		// Check for collision 
		for (int i = 0; i < bulletColliders.size(); ++i)
		{
			for (int j = 0; j < worldColliders.size(); ++j)
			{
				if (!bulletColliders[i]->CheckCollision(*worldColliders[j]))
					continue;

				// Collision
				std::cout << "collision" << std::endl;
				mtrx::Rigidbody* bullet = bulletRbs[i];
				mtrx::Collider* collider = bulletColliders[i];

				worldRbs[j]->AddForceAtPoint(glm::fastNormalize(bullet->GetVelocity()) * 100.f, bullet->GetPosition());

				world.RemoveRigidbody(bullet);
				transformsToRender.erase(&bullet->GetTransform());
				bulletRbs.erase(bulletRbs.begin() + i);
				bulletColliders.erase(bulletColliders.begin() + i);

				delete collider;
				--i;
				break;
			}
		}

		// Update the demo
		Demo::Update();
	}
}

void CollisionDemo::InputCheck()
{
	if (application.inputSystem->GetKeyDown(GLFW_KEY_SPACE))
		Shoot();
}

void CollisionDemo::Shoot()
{
	// We are shooting a bullet like an fps game
	float extents[3] = {0.1f, 0.1f, 0.1f};
	float mass = 1.f;
	glm::vec3 forward = application.camera->GetForward();
	mtrx::Rigidbody* bullet = new mtrx::Rigidbody(mass, false, application.camera->GetTransform().GetPosition() + forward * 0.5f, glm::angleAxis(0.f, mtrx::worldUp), glm::vec3(0.1, 0.1, 0.1), mtrx::GenerateCuboidIT(mass, extents));
	mtrx::Collider* collider = new mtrx::BoxCollider(bullet->GetTransform());

	// Add a force going in the forward direction from the camera with some scalar for magnitude
	bullet->AddForce(forward * 1000.f);

	bulletRbs.push_back(bullet);
	bulletColliders.push_back(collider);
	transformsToRender.insert(&bullet->GetTransform());
	world.AddRigidbody(bullet);
}