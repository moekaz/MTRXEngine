/*
	Author: Mohamed Kazma
	Description: This should be the main physics engine file that will implement what is needed by the engine
*/

#pragma once
#ifndef MTRX_H
#define MTRX_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <glm/vec3.hpp>

#include "Collider.h"
#include "Mat3.h"

class MTRX
{
public:
	std::map<int , Collider> collider;		// Store the colliders that we want to run through

	MTRX();								// Constructor
	~MTRX();							// Destructor

	void Update();						// Update the game engine values
	
	void NarrowPhase();					// Narrow phase collision detection checks
	void BroadPhase();					// Broad phase collision detection checks

	Collider* Raycast();				// Raycast without any filtering of colliders
	Collider* RaycastFiltered();		// Raycast with filtering out some colliders
private:
protected:
};
#endif // MTRX_H