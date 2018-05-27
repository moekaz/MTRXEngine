/*
	Author: Mohamed Kazma
	Description: Cpp implementation of a 3x3 matrix
*/

#include "../headers/Mat3.h"

// Constructor
Mat3::Mat3(Vector3D col1 , Vector3D col2 , Vector3D col3)
{
	matrix[0] = col1;
	matrix[1] = col2;
	matrix[2] = col3;
}

// Constructor
Mat3::Mat3(float a, float b, float c, float d, float e, float f, float g, float h, float i)
{
	matrix[0] = Vector3D(a , b , c);
	matrix[1] = Vector3D(d , e , f);
	matrix[2] = Vector3D(g , h , i);
}

// Destructor
Mat3::~Mat3(){}

/* Functions */

// Inverse of a 3x3 matrix
Mat3 InverseMatrix()
{
	return NULL;
}

/* Operator overloading */

// Print the values of the matrix
std::ostream& operator<<(std::ostream& os , Mat3& matrix)
{
	os << matrix[0].x << " , " << matrix[0].y << " , " << matrix[0].z << "\n" << matrix[1].x << " , " 
		<< matrix[1].y << " , " << matrix[1].z << "\n" << matrix[2].x << " , " << matrix[2].y << " , "
		<< matrix[2].z;
	return os;
}

// Return a certain column of the matrix
Vector3D Mat3::operator[](int index)
{
	if (index < 0 || index > 2) return NULL;
	return matrix[index];
}



