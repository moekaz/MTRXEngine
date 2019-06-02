/*
*/

#pragma once

#include <entities/Rigidbody.h>
#include <forceGenerators/RigidbodyGenerators/rb_ForceGenerationRegistry.h>
#include <IUpdateable.h>

namespace mtrx
{
	// Each rigidbody will hold a force registry that will update this rigidbody
	struct rbForceGenerators
	{
		Rigidbody* rb;
		rb_ForceGenerationRegistry* registry;
	};

	class RigidbodyManager : public IUpdateable
	{
	public:
		std::list<rbForceGenerators> forceGenerators;
		std::list<Rigidbody> rigidbodies;

		RigidbodyManager();
		~RigidbodyManager();

		virtual void PhysicsUpdate() override;
		void UpdateRigidbodies();
		void UpdateForces();
		void GenerateCollisions();
	};
}
