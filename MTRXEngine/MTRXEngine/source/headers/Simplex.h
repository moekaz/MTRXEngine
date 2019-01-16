/*
	Author: Mohamed Kazma
	Description: A simplex is the simplest shape that we can have that can give us a bounding shape that can bound a point in space 
	This is useful for something like GJK since the point of it is to bound the center (0, 0, 0) within the simplest shape that can hold it
	which is a tetrahedron
*/

#pragma once

namespace MTRX
{
	class Simplex
	{
	public:
		glm::vec3* b;
		glm::vec3* c;
		glm::vec3* d;
		int size;			// The size of the simplex this will be at most 3 (b, c, d)

		Simplex();			// Constructor
		~Simplex();			// Destructor
	};
}