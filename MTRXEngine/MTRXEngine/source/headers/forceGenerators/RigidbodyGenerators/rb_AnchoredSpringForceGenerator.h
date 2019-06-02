/*
	Author: Mohamed Kazma
	Description: A spring force generator that uses anchor points to generate the forces
	This can either be the center of a particle or just some fixed anchor its the same calculation
*/

#pragma once

#include <forceGenerators/RigidbodyGenerators/IRigidbodyForceGenerator.h>
#include <entities/Rigidbody.h>
#include <Defs.h>

namespace mtrx
{
	class rb_AnchoredSpringForceGenerator : public IRigidbodyForceGenerator
	{
	public:
		glm::vec3* anchorPoint;
		SpringData spring;

		rb_AnchoredSpringForceGenerator(glm::vec3* anchorPoint, float stiffness, float restLength);
		~rb_AnchoredSpringForceGenerator();

		virtual void UpdateForces(Rigidbody* rb) override;

		inline void SetAnchorPoint(glm::vec3* point) { anchorPoint = point; }
	};
}

