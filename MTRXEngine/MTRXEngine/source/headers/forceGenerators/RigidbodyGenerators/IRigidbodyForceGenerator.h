#pragma once

#include <entities/Rigidbody.h>

namespace mtrx
{
	/**
	 * @brief Force generation interface used to apply forces on rigidbodies
	 * 
	 */
	class IRigidbodyForceGenerator
	{
	public:

		/**
		 * @brief Apply a certain force onto the given rigidbodies
		 * 
		 * @param rb The rigidbody we want to apply the force onto
		 * @param deltaTime The time elapsed since the previous frame
		 */
		virtual void UpdateForces(Rigidbody* rb, float deltaTime) = 0;
	};
}