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

#include "Collider.h"
#include "Vector3D.h"
#include "Mat3.h"

class MTRX
{
public:
	std::vector<Collider> collider;		// Store the colliders that we want to run through

	MTRX();								// Constructor
	~MTRX();							// Destructor

	void Update();						// Update the game engine values
	
	void NarrowPhase();					// Narrow phase collision detection checks
	void BroadPhase();					// Broad phase collision detection checks
private:
protected:
};
#endif // MTRX_H