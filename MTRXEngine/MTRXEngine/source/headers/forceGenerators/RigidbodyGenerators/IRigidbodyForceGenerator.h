/*
	Author: Mohamed Kazma
	Description: Interface that allows us to define different force patterns for different types of objects
*/
#pragma once

#include <entities/Rigidbody.h>

namespace mtrx
{
	class IRigidbodyForceGenerator
	{
	public:
		virtual void UpdateForces(Rigidbody* rb, float deltaTime) = 0;
	};
}