#pragma once

#include <../Demos/Demo.h>
#include <entities/Rigidbody.h>
#include <forceGenerators/RigidbodyGenerators/rb_GravityForceGenerator.h>
#include <Defs.h>

class CollisionDemo : public Demo
{
public:
	mtrx::Rigidbody projectile;

	CollisionDemo();
	~CollisionDemo();

	virtual void Update() override;
	virtual void InputCheck() override;
};