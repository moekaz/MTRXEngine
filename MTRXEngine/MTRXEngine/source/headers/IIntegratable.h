/*
	Author: Mohamed Kazma
	Description: Interface for all updateable classes
*/

#pragma once

namespace mtrx
{
	class IIntegratable
	{
	public:
		virtual void Integrate(float deltaTime) = 0;	// Call a physics update

	private:
	protected:
	};
}