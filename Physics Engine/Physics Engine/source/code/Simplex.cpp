/*
	Author: Mohamed Kazma
	Description: Implementation of a simplex
*/

#include "../headers/Simplex.h"

Simplex::Simplex()
{
	b = c = d = Vector3D::zero;
	size = 0;
}