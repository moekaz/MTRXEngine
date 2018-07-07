/*
	Author: Mohamed Kazma
	Description: Implementation of a simplex
*/

#include "../headers/Simplex.h"

// Constructor
Simplex::Simplex()
{
	b = c = d = Vector3D::zero;
	size = 0;
}

// Destructor
Simplex::~Simplex() {}