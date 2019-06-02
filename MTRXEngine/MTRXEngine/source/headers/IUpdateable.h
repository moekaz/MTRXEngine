/*
	Author: Mohamed Kazma
	Description: Interface for all updateable classes
*/

#pragma once

namespace mtrx
{
	class IUpdateable
	{
	public:
		virtual void PhysicsUpdate() = 0;	// Call a physics update

	private:
	protected:
	};
}