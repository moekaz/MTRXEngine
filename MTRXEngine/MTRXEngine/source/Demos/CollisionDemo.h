#pragma once

#include <../Demos/Demo.h>
#include <entities/Rigidbody.h>
#include <forceGenerators/RigidbodyGenerators/rb_GravityForceGenerator.h>
#include <Defs.h>
#include <colliders/Collider.h>
#include <colliders/SphereCollider.h>
#include <colliders/CapsuleCollider.h>
#include <../Renderer/CollisionDemoUI.h>
#include <colliders/OOBBCollider.h>

// TBD: FIX THIS DEMO
class CollisionDemo : public Demo
{
public:	
	std::vector<mtrx::Rigidbody*> worldRbs;
	std::vector<mtrx::Collider*> worldColliders;
	std::vector<mtrx::Rigidbody*> bulletRbs;
	std::vector<mtrx::Collider*> bulletColliders;

	CollisionDemo();
	~CollisionDemo() = default;

	virtual void Update() override;
	virtual void InputCheck() override;

	void Shoot();
};