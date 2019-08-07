#include <PrecompiledHeader.h>
#include <../Demos/CollisionDemo.h> 

CollisionDemo::CollisionDemo() : Demo("COLLISION DEMO")
{
	srand(time(0)); // Seed for random

	// Create game obstacles  
	int numObstacles = 20;
	for (int i = 0; i < numObstacles; ++i)
	{
		float extents[3] = { 1, 1, 1 };
		float mass = 2.f;
		glm::quat orientation1 = glm::angleAxis(0.f, mtrx::worldUp);
		
		float x = rand() % 50;
		float y = rand() % 50;
		float z = rand() % 50;

		mtrx::Rigidbody* body = new mtrx::Rigidbody(mass, false, glm::vec3(x, y, z), orientation1, glm::vec3(extents[0], extents[1], extents[2]), mtrx::GenerateCuboidIT(mass, extents));
		mtrx::Collider* collider = new mtrx::BoxCollider(body->GetPosition());
		body->SetAngularDamping(0.8f);
		body->SetLinearDamping(0.99f);

		// Capusle collider
		//collider1 = new mtrx::CapsuleCollider(body1.GetPosition());

		// Sphere Colliders
		//collider1 = new mtrx::SphereCollider(body1.GetPosition());

		worldRbs.push_back(body);
		worldColliders.push_back(collider);
		rbManager.AddRigidbody(body);
		transformsToRender.insert(&body->GetTransform());
	}
}

CollisionDemo::~CollisionDemo()
{}

void CollisionDemo::Update()
{
	// Thinking about creating a fps shooting demo with collision detection and force generation
		// This is just a reference point in world space
	mtrx::Transform center =
	{
		glm::vec3(),
		glm::angleAxis(0.f, mtrx::worldUp),
		glm::vec3(0.1f, 0.1f, 0.1f),
	};
	transformsToRender.insert(&center);

	// Update loop
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

				worldRbs[j]->AddForceAtPoint(glm::fastNormalize(bullet->GetVelocity()) * 1500.f, bullet->GetPosition());

				rbManager.RemoveRigidbody(bullet);
				transformsToRender.erase(&bullet->GetTransform());
				bulletRbs.erase(bulletRbs.begin() + i);
				bulletColliders.erase(bulletColliders.begin() + i);

				delete bullet;
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
	{
		Shoot();
		//body1.AddForce(glm::vec3(-10, 0, 0));
		//body2.AddForce(glm::vec3(10, 0, 0));
	}
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
	bullet->AddForce(forward * 2000.f);

	bulletRbs.push_back(bullet);
	bulletColliders.push_back(collider);
	transformsToRender.insert(&bullet->GetTransform());
	rbManager.AddRigidbody(bullet);
}