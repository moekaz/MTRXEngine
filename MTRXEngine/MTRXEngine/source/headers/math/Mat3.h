/*
	Author: Mohamed Kazma
	Description: implementation of a 3x3 matrix 
*/

#pragma once

#include <math/Vector3D.h>

namespace mtrx
{
	class Mat3
	{
	public:
		/* Constructors and Destructors */
		Mat3(const Vector3D& row1 = Vector3D::zero, const Vector3D& row2 = Vector3D::zero, const Vector3D& row3 = Vector3D::zero);
		Mat3(float x1 = 0, float y1 = 0, float z1 = 0, float x2 = 0, float y2 = 0, float z2 = 0, float x3 = 0, float y3 = 0, float z3 = 0);
		~Mat3();

		/* Functions */
		Mat3 InverseMatrix();																// Find the inverse matrix of this matrix
		Mat3 Transpose();																	// Find the transpose of a matrix
		Mat3 AdjugateMatrix();																// Find the adjugate of a matrix
		float Determinant();																// Find the determinant of the matrix

		/* Operator Overloading */
		friend std::ostream& operator<<(std::ostream&, const Mat3&);						// Print out values of the matrix
		Vector3D& operator[](int);															// Getting the rows as an array
		const Vector3D& operator[](int) const;												// Used for consts
		Mat3 operator+(const Mat3&);														// Adding 2 matrices		
		Mat3 operator+=(const Mat3&);														// Adding 2 matrices using +=
		Mat3 operator-(const Mat3&);														// Subtracting 2 matrices
		Mat3 operator-=(const Mat3&);														// Subtracting 2 matrices using -=
		Mat3 operator*(const Mat3&);														// Multiplying 2 matrices
		Mat3 operator*(float);																// Multiplying a matrix by a float
		Mat3 operator*=(const Mat3&);														// Multiplying 2 matrices using *=
		Mat3 operator*=(float);																// Multiplying a matrix by a float *=

	private:
		/* Member Variables */
		Vector3D matrix[3];																	// Values of the matrix

	protected:
	};
}