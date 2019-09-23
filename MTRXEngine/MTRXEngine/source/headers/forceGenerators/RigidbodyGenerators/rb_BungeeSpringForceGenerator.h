#pragma once

#include <entities/Rigidbody.h>
#include <forceGenerators/RigidbodyGenerators/rb_AnchoredSpringForceGenerator.h>

namespace mtrx
{
	class rb_BungeeSpringForceGenerator : public rb_AnchoredSpringForceGenerator
	{
	public:
		rb_BungeeSpringForceGenerator(glm::vec3* anchorPoint, float stiffness, float restLength);
		~rb_BungeeSpringForceGenerator();

		virtual void UpdateForces(Rigidbody* rb, float deltaTime) override;
	};
}
