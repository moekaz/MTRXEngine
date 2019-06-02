/*
	Author: Mohamed Kazma
	Description: Allows us to have an API for force generators
*/

#pragma once

#include <forceGenerators/RigidbodyGenerators/IRigidbodyForceGenerator.h>

namespace mtrx
{
	class rb_ForceGenerationRegistry
	{
	public:
		rb_ForceGenerationRegistry();
		~rb_ForceGenerationRegistry();

		inline void AddForceGenerator(IRigidbodyForceGenerator* forceGenerator) { forceGenerators.push_back(forceGenerator); }
		inline void RemoveForceGenerator(const int index) { forceGenerators.erase(forceGenerators.begin() + index); }
		void RemoveForceGenerator(const IRigidbodyForceGenerator* forceGenerator); // Remove a specific force generator
		inline void ClearForceGenerators() { forceGenerators.clear(); }
		void UpdateForceGenerators(Rigidbody* particle); // Update the force generators using a rigidbody

	private:
		std::vector<IRigidbodyForceGenerator*> forceGenerators; // The force generators that we going to be using
	};
}

