/*
	Author: Mohamed Kazma
	Description: A very inaccurate implementation of a stiff spring using force averages 
	(This is not accurate and to be used in very limited positions velocity simulation can be incorrect and doesn't take other forces into consideration
	and there is no rest length for the spring and is also to be used on one particle instead of 2)
*/

#pragma once

#include <forceGenerators/RigidbodyGenerators/IRigidbodyForceGenerator.h>
#include <entities/Rigidbody.h>
#include <Defs.h>

namespace mtrx
{
	class rb_StiffSpringForceGenerator : public IRigidbodyForceGenerator
	{
	public:
		float springStiffness; // Stiffness constant of the spring
		glm::vec3* anchorPoint; // Anchor point that the spring is hung from
		float springDamping; // Damping caused by by the spring forces

		virtual void UpdateForces(Rigidbody* rb);

		rb_StiffSpringForceGenerator(glm::vec3* anchorPoint, float springStiffness, float springDamping);
		~rb_StiffSpringForceGenerator();

		inline void SetAnchorPoint(glm::vec3* point) { anchorPoint = point; }
	};
}