#include <PrecompiledHeader.h>
#include <../Demos/CollisionDemo.h> 

CollisionDemo::CollisionDemo() : Demo("COLLISION DEMO")
{}

CollisionDemo::~CollisionDemo()
{}

void CollisionDemo::Update()
{
	Demo::Update();
}

void CollisionDemo::InputCheck()
{}

//int main()
//{
//
//	bool started = false;
//	mtrx::Collider* collider = new mtrx::CapsuleCollider();
//	mtrx::Collider* collider1 = new mtrx::CapsuleCollider();
//	
//	//// Rigidbodies
//	//glm::quat orientation = glm::angleAxis(0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
//	//mtrx::Rigidbody body1 = mtrx::Rigidbody(1.f, false, glm::vec3(0.f, 1.f, 0.f), orientation, glm::vec3(1.f, 1.f, 1.f));
//	//float extents[3] = { 1.f, 1.f, 1.f };
//	//body1.SetInverseInertiaTensor(mtrx::GenerateCuboidIT(1.f, extents));
//
//	//// Second box
//	//glm::quat orientation1 = glm::angleAxis(0.0f, glm::vec3(0, 0, 0));
//	//mtrx::Rigidbody body2 = mtrx::Rigidbody(1.f, false, glm::vec3(-3.f, 1.f, 0.f), orientation1, glm::vec3(1.f, 1.f, 1.f));
//	//body1.SetInverseInertiaTensor(mtrx::GenerateCuboidIT(1.f, extents));
//
//	//body1 = mtrx::Rigidbody(1.f, false, glm::vec3(0.f, 1.f, 0.f), orientation, glm::vec3(1.f, 1.f, 1.f));
//	//body2 = mtrx::Rigidbody(1.f, false, glm::vec3(-3.f, 1.f, 0.f), orientation1, glm::vec3(1.f, 1.f, 1.f));
//
//	//body1.AddForce(glm::vec3(-10.f, 0.f, 0.f));
//	//body2.AddForce(glm::vec3(10.f, 0.0f, 0.0f));
//
//	//transformsToRender.push_back(body1.GetTransform());
//	//transformsToRender.push_back(body2.GetTransform());
//	//rbManager.AddForceGenerator(&body1, &gravityGenerator);
//	//rbManager.AddForceGenerator(&body1, &buoyancyGenerator);
//
//	//rbManager.RemoveRigidbody(&artillery);
//	//transformsToRender.erase(transformsToRender.begin() + transformsToRender.size() - 1);
//	//glm::quat orientation1 = glm::angleAxis(0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
//	//artillery = mtrx::Rigidbody(2.f, false, glm::vec3(-1.f, 0.f, 0.f), orientation1, glm::vec3(1.f, 1.f, 1.f));
//	//artillery.SetAngularDamping(0.9f);
//	//artillery.SetLinearDamping(0.9f);
//	//transformsToRender.push_back(artillery.GetTransform());
//
//	//rbManager.AddRigidbody(&artillery);
//	//rbManager.AddForceGenerator(&artillery, &gravityGenerator);
//	//artillery.SetVelocity(glm::vec3(3, 2, 0));
//
//	//artillery.SetAcceleration(glm::vec3(0, -2.f, 0));
//	//artillery.AddForce(glm::vec3(3000.f, 2000.f, 0));
//	//artillery.AddForceAtPoint(glm::vec3(0.0f, 0.f, -1000.f), artillery.GetPosition() + glm::vec3(0.0f, 0.5f, 0.0f));
//
//	if (started)
//	{
//		// Update the colliders
//		//collider->SetPosition(body1.GetPosition());
//		//collider1->SetPosition(body2.GetPosition());
//
//		//glm::vec3 pos = collider->GetPosition();
//		//glm::vec3 pos1 = collider1->GetPosition();
//		//std::cout << "position1: " << pos.x << " " << pos.y << " " << pos.z << std::endl;
//		//std::cout << "position2: " << pos1.x << " " << pos1.y << " " << pos1.z << std::endl;
//
//		//if (collider->CheckCollision(*collider1))
//		//{
//		//	std::cout << "collision" << std::endl;
//		//	transformsToRender.clear();
//		//	rbManager.RemoveRigidbody(&body1);
//		//	rbManager.RemoveRigidbody(&body2);
//		//	started = false;
//		//}
//	}
//}