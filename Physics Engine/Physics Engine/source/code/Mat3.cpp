/*
	Author: Mohamed Kazma
	Description: Cpp implementation of a 3x3 matrix
*/

#include "../headers/Mat3.h"

// Constructor
Mat3::Mat3(Vector3D& col1 , Vector3D& col2 , Vector3D& col3)
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

// Inverse of this 3x3 matrix
Mat3 Mat3::InverseMatrix()
{
	return AdjugateMatrix() * (1 / Determinant());
}

// Finding the transpose of this 3x3 matrix
Mat3 Mat3::Transpose()
{
	Vector3D col1 = Vector3D(matrix[0].x , matrix[1].x , matrix[2].x);
	Vector3D col2 = Vector3D(matrix[0].y , matrix[1].y , matrix[2].y);
	Vector3D col3 = Vector3D(matrix[0].z , matrix[1].z , matrix[2].z);

	return Mat3(col1, col2, col3);
}

// Finding the determinant of the 3x3 matrix
float Mat3::Determinant()
{
	return matrix[0].x * ((matrix[1].y * matrix[2].z) - (matrix[2].y * matrix[1].z)) -
		   matrix[1].x * ((matrix[0].y * matrix[2].z) - (matrix[2].y * matrix[0].z)) +  
		   matrix[2].x * ((matrix[0].y * matrix[1].z) - (matrix[1].y * matrix[0].z));
}

// Adjugate matrix
Mat3 Mat3::AdjugateMatrix()
{
	float a = (matrix[1].y * matrix[2].z) - (matrix[2].y * matrix[1].z);
	float b = (matrix[0].y * matrix[2].z) - (matrix[2].y * matrix[0].z);
	float c = (matrix[0].y * matrix[1].z) - (matrix[1].y * matrix[0].z);
	float d = (matrix[1].x * matrix[2].z) - (matrix[2].x * matrix[1].z);
	float e = (matrix[0].x * matrix[2].z) - (matrix[2].x * matrix[0].z);
	float f = (matrix[0].x * matrix[1].z) - (matrix[1].x * matrix[0].z);
	float g = (matrix[1].x * matrix[2].y) - (matrix[2].x * matrix[1].y);
	float h = (matrix[0].x * matrix[2].y) - (matrix[2].x * matrix[0].y);
	float i = (matrix[0].x * matrix[1].y) - (matrix[1].x * matrix[0].y);

	return Mat3(a , -b , c , -d , e , -f , g , -h , i);
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
Vector3D& Mat3::operator[](int index)
{
	if (index < 0 || index > 2) throw std::out_of_range("shit just broke");
	return matrix[index];
}

// Matrix addition 
Mat3 Mat3::operator+(Mat3& mat)
{
	Vector3D col1 = matrix[0] + mat[0];
	Vector3D col2 = matrix[1] + mat[1];
	Vector3D col3 = matrix[2] + mat[2];

	return Mat3(col1, col2, col3);
}

// Matrix Subtraction
Mat3 Mat3::operator-(Mat3& mat)
{
	Vector3D col1 = matrix[0] - mat[0];
	Vector3D col2 = matrix[1] - mat[1];
	Vector3D col3 = matrix[2] - mat[2];
	
	return Mat3(col1, col2, col3);
}

// Matrix Multiplication
Mat3 Mat3::operator*(Mat3& mat)
{
	Vector3D row1 = Vector3D(matrix[0].x, matrix[1].x, matrix[2].x);
	Vector3D row2= Vector3D(matrix[0].y, matrix[1].y, matrix[2].y);
	Vector3D row3 = Vector3D(matrix[0].z, matrix[1].z, matrix[2].z);

	Vector3D col1 = row1 * mat[0];
	Vector3D col2 = row2 * mat[1];
	Vector3D col3 = row3 * mat[2];

	return Mat3(col1, col2, col3);
}

// Matrix by float multiplication
Mat3 Mat3::operator*(float scalar)
{
	Vector3D col1 = matrix[0] * scalar;
	Vector3D col2 = matrix[1] * scalar;
	Vector3D col3 = matrix[2] * scalar;

	return Mat3(col1 , col2 , col3);
}

// Matrix Division
Mat3 Mat3::operator/(Mat3& mat)
{
	//use the inverse matrix to be able to do this A x B^-1
	Mat3 inverse = mat.InverseMatrix();
	return *this * inverse;
}

// Matrix += addition
Mat3 Mat3::operator+=(Mat3& mat)
{
	*this = *this + mat;
	return *this;
}

// Matrix -= subtraction
Mat3 Mat3::operator-=(Mat3& mat)
{
	*this = *this - mat;
	return *this;
}

// Matrix *= multiplication
Mat3 Mat3::operator*=(Mat3& mat)
{
	*this = *this * mat;
	return *this;
}

// Matrix float *= multiplication
Mat3 Mat3::operator*=(float scalar)
{
	*this = *this * scalar;
	return *this;
}

// Matrix /= division
Mat3 Mat3::operator/=(Mat3& mat)
{
	*this = *this / mat;
	return  *this;
}