#include <PrecompiledHeader.h>
#include <../Demos/BuoyancyDemo.h>

BuoyancyDemo::BuoyancyDemo() : Demo("Buoyancy Demo", 1280, 720)
{}

void BuoyancyDemo::Update()
{
	mtrx::Transform center =
	{
		glm::vec3(0, 0, 0),
		glm::angleAxis(0.f, mtrx::worldUp),
		glm::vec3(0.05f, 0.05f, 0.05f),
	};
	transformsToRender.insert(&center);

	application.camera->GetTransform().SetPosition(glm::vec3(-2.f, 0, 15.f));

	// Setup body
	float mass = 500.f;
	float extents[] = { 1.f, 1.f, 1.f };
	float linearDamping = 0.98f;
	float gravitationAcceleration = -9.8f;
	glm::vec3 gravity = glm::vec3(0, gravitationAcceleration, 0);
	body = new mtrx::Rigidbody(mass, false, glm::vec3(-2.f, 6.f, 0), glm::angleAxis(0.f, mtrx::worldUp), glm::vec3(1, 1, 1), mtrx::GenerateCuboidIT(mass, extents));
	std::shared_ptr<mtrx::rb_BuoyancyForceGenerator> buoyancyGenerator = std::make_shared<mtrx::rb_BuoyancyForceGenerator>(gravity, 1.f, 3.f);
	std::shared_ptr<mtrx::rb_GravityForceGenerator> gravityGenerator = std::make_shared<mtrx::rb_GravityForceGenerator>(gravity);
	body->SetLinearDamping(linearDamping);

	// Add the relevant info
	world.AddRigidbody(body);
	world.AddForceGenerator(body, buoyancyGenerator);
	world.AddForceGenerator(body, gravityGenerator);
	transformsToRender.insert(&body->GetTransform());

	// Create UI
	BuoyancyDemoUI ui = BuoyancyDemoUI("Buoyancy Demo", glm::vec2(400, 300), &linearDamping, &gravitationAcceleration, &buoyancyGenerator->liquidLevel, &buoyancyGenerator->liquidDensity);
	UILayer::AddUIPanel(&ui);

	while (!application.window.ShouldClose())
	{
		// Workaround i guess
		body->SetLinearDamping(linearDamping);
		gravityGenerator->gravitationalAcceleration.y = gravitationAcceleration;
		buoyancyGenerator->gravitationalAcceleration.y = gravitationAcceleration;
		center.GetPosition().y = buoyancyGenerator->liquidLevel;
		Demo::Update();
	}
}

void BuoyancyDemo::InputCheck()
{
	if (application.inputSystem->GetKeyDown(GLFW_KEY_SPACE))
	{
		float mass = 500.f;
		float extents[] = { 1.f, 1.f, 1.f };
		body->SetPosition(glm::vec3(-2.f, 6.f, 0));
		body->ClearAccumulators();
	}
}

