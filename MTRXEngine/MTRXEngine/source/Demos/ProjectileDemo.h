#pragma once

#include <../Demos/Demo.h>
#include <entities/Rigidbody.h>
#include <forceGenerators/RigidbodyGenerators/rb_GravityForceGenerator.h>
#include <Defs.h>
#include <ProjectileDemoUI.h>

class ProjectileDemo : public Demo
{
public:
	mtrx::Rigidbody projectile;
	mtrx::rb_GravityForceGenerator gravityGenerator;
	int projectileType;

	ProjectileDemo();
	~ProjectileDemo();

	virtual void Update() override;
	virtual void InputCheck() override;
};