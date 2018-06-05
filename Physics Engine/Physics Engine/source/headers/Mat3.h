/*
	Author: Mohamed Kazma
	Description: implementation of a 3x3 matrix 
*/

#ifndef MAT3_H
#define MAT3_H

#include <iostream>
#include "../headers/Vector3D.h"

//might need to implement this in a 2d float array instead since vector3's subscript operator is inefficient
class Mat3
{
public:
	/* Constructors and Destructors */
	Mat3(Vector3D , Vector3D , Vector3D);
	Mat3(float x1 = 0 , float y1 = 0 , float z1 = 0 , float x2 = 0 , float y2 = 0 , float z2 = 0 , float x3 = 0 , float y3 = 0 , float z3 = 0); 
	~Mat3();	

	/* Functions */
	Mat3 InverseMatrix();																// Find the inverse matrix of this matrix
	Mat3 Transpose();																	// Find the transpose of a matrix
	Mat3 AdjugateMatrix();																// Find the adjugate of a matrix
	float Determinant();																// Find the determinant of the matrix

	/* Operator Overloading */
	friend std::ostream& operator<<(std::ostream& , const Mat3&);								// Print out values of the matrix
	Vector3D& operator[](int);															// Getting the rows as an array
	Mat3 operator+(Mat3&);																// Adding 2 matrices		
	Mat3 operator+=(Mat3&);																// Adding 2 matrices using +=
	Mat3 operator-(Mat3&);																// Subtracting 2 matrices
	Mat3 operator-=(Mat3&);																// Subtracting 2 matrices using -=
	Mat3 operator*(Mat3&);																// Multiplying 2 matrices
	Mat3 operator*(float);																// Multiplying a matrix by a float
	Mat3 operator*=(Mat3&);																// Multiplying 2 matrices using *=
	Mat3 operator*=(float);																// Multiplying a matrix by a float *=
	Mat3 operator/(Mat3&);																// Does division exist for matrices?
	Mat3 operator/=(Mat3&);																// Same using /=

private:
	/* Member Variables */
	Vector3D matrix[3];																	// Values of the matrix

protected:
};
#endif // MAT3_H