/*
	Author: Mohamed Kazma
	Description: Implementation of a simplex
*/

#include "../headers/Simplex.h"

// Constructor
Simplex::Simplex()
{
	b = c = d = glm::vec3();
	size = 0;
}

// Destructor
Simplex::~Simplex() {}