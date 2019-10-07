#include <PrecompiledHeader.h>
#include <../Demos/BuoyancyDemo.h>

BuoyancyDemo::BuoyancyDemo() : Demo("Buoyancy Demo", 1280, 720)
{}

BuoyancyDemo::~BuoyancyDemo()
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

	application.camera->GetTransform().SetPosition(glm::vec3(0, 0, 10.f));

	// Setup body
	float mass = 500.f;
	float extents[] = { 1.f, 1.f, 1.f };
	glm::vec3 gravity = glm::vec3(0, -0.5f, 0);
	body = mtrx::Rigidbody(mass, false, glm::vec3(-2.f, 6.f, 0), glm::angleAxis(0.f, mtrx::worldUp), glm::vec3(1, 1, 1), mtrx::GenerateCuboidIT(mass, extents));
	mtrx::rb_BuoyancyForceGenerator buoyancyGenerator = mtrx::rb_BuoyancyForceGenerator(gravity, 1.f, 3.f);
	mtrx::rb_GravityForceGenerator gravityGenerator = mtrx::rb_GravityForceGenerator(gravity);
	body.SetLinearDamping(0.97f);

	// Add the relevant info
	rbManager.AddRigidbody(&body);
	rbManager.AddForceGenerator(&body, &buoyancyGenerator);
	rbManager.AddForceGenerator(&body, &gravityGenerator);
	transformsToRender.insert(&body.GetTransform());

	while (!application.window.ShouldClose())
	{
		Demo::Update();
	}
}

void BuoyancyDemo::InputCheck()
{}

