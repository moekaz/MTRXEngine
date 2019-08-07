/*
	Author: Mohamed Kazma
	Description: This should be the main physics engine file that will implement what is needed by the engine
*/

#pragma once

#include <IUpdateable.h>
#include <colliders/Collider.h>

//TBD: Implement the main physics engine manager that we will be using for updates and etc...
namespace mtrx
{
	class mtrx : public IUpdateable
	{
	public:
		std::unordered_map<int, Collider> collider;		// Store the colliders that we want to run through

		mtrx();								// Constructor
		~mtrx();							// Destructor

		void PhysicsUpdate();				// Update the game engine values
		void NarrowPhase();					// Narrow phase collision detection checks
		void BroadPhase();					// Broad phase collision detection checks

		Collider* Raycast();				// Raycast without any filtering of colliders
		Collider* RaycastFiltered();		// Raycast with filtering out some colliders
	private:
	protected:
	};
}