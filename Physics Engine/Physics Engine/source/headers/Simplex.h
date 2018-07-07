/*
	Author: Mohamed Kazma
	Description: 
*/

#ifndef SIMPLEX_H
#define SIMPLEX_H

#include "Vector3D.h"

class Simplex
{
public:
	Vector3D b, c, d;
	int size;
	Simplex();
};
#endif // !SIMPLEX_H
