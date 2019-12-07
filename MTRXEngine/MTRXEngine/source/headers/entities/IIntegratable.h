/*
	Author: Mohamed Kazma
	Description: Interface for all updateable classes
*/

#pragma once

namespace mtrx
{
	/**
	 * @brief Interface for integration 
	 * PS: Not used that much really
	 * 
	 */
	class IIntegratable
	{
	public:
		/**
		 * @brief Integration functionality
		 * 
		 * @param deltaTime Time elapsed from previous frame
		 */
		virtual void Integrate(float deltaTime) = 0;

	private:
	protected:
	};
}