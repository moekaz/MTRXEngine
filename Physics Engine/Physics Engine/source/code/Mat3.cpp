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

// Inverse of this 3x3 matrix
Mat3 Mat3::InverseMatrix()
{
	return AdjugateMatrix() * (1 / Determinant());
}

// Finding the transpose of this 3x3 matrix
Mat3 Mat3::Transpose()
{
	Vector3D col1 = Vector3D(matrix[0][0], matrix[1][0] , matrix[2][0]);
	Vector3D col2 = Vector3D(matrix[0][1] , matrix[1][1] , matrix[2][1]);
	Vector3D col3 = Vector3D(matrix[0][2] , matrix[1][2] , matrix[2][2]);

	return Mat3(col1, col2, col3);
}

// Finding the determinant of the 3x3 matrix
float Mat3::Determinant()
{
	return matrix[0][0] * ((matrix[1][1] * matrix[2][2]) - (matrix[2][1] * matrix[1][2])) -
		   matrix[1][0] * ((matrix[0][1] * matrix[2][2]) - (matrix[2][1] * matrix[0][2])) +  
		   matrix[2][0] * ((matrix[0][1] * matrix[1][2]) - (matrix[1][1] * matrix[0][2]));
}

// Adjugate matrix
Mat3 Mat3::AdjugateMatrix()
{
	float a = (matrix[1][1] * matrix[2][2]) - (matrix[2][1] * matrix[1][2]);
	float b = (matrix[0][1] * matrix[2][2]) - (matrix[2][1] * matrix[0][2]);
	float c = (matrix[0][1] * matrix[1][2]) - (matrix[1][1] * matrix[0][2]);
	float d = (matrix[1][0] * matrix[2][2]) - (matrix[2][0] * matrix[1][2]);
	float e = (matrix[0][0] * matrix[2][2]) - (matrix[2][0] * matrix[0][2]);
	float f = (matrix[0][0] * matrix[1][2]) - (matrix[1][0] * matrix[0][2]);
	float g = (matrix[1][0] * matrix[2][1]) - (matrix[2][0] * matrix[1][1]);
	float h = (matrix[0][0] * matrix[2][1]) - (matrix[2][0] * matrix[0][1]);
	float i = (matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]);

	return Mat3(a , -b , c , -d , e , -f , g , -h , i);
}

/* Operator overloading */

// Return a certain column of the matrix
Vector3D& Mat3::operator[](int index)
{
	if (index < 0 || index > 2) throw std::out_of_range("shit just broke");
	return matrix[index];
}

// Matrix addition 
Mat3 Mat3::operator+(const Mat3& mat)
{
	return Mat3((*this)[0] + mat[0], (*this)[1] + mat[1], (*this)[2] + mat[2]);
}

// Matrix Subtraction
Mat3 Mat3::operator-(const Mat3& mat)
{
	return Mat3((*this)[0] - mat[0], (*this)[1] - mat[1], (*this)[2] - mat[2]);
}

// Matrix Multiplication
Mat3 Mat3::operator*(const Mat3& mat)
{
	Vector3D col1 = Vector3D(mat[0][0], mat[1][0], mat[2][0]);
	Vector3D col2 = Vector3D(mat[0][1], mat[1][1], mat[2][1]);
	Vector3D col3 = Vector3D(mat[0][2], mat[1][2], mat[2][2]);
	
	// Lets hope for some compiler optimizations
	float a = ((*this)[0] * col1)[0] + ((*this)[0] * col1)[1] + ((*this)[0] * col1)[2];
	float b = ((*this)[0] * col2)[0] + ((*this)[0] * col2)[1] + ((*this)[0] * col2)[2];
	float c = ((*this)[0] * col3)[0] + ((*this)[0] * col3)[1] + ((*this)[0] * col3)[2];
	float d = ((*this)[1] * col1)[0] + ((*this)[1] * col1)[1] + ((*this)[1] * col1)[2];
	float e = ((*this)[1] * col2)[0] + ((*this)[1] * col2)[1] + ((*this)[1] * col2)[2];
	float f = ((*this)[1] * col3)[0] + ((*this)[1] * col3)[1] + ((*this)[1] * col3)[2];
	float g = ((*this)[2] * col1)[0] + ((*this)[2] * col1)[1] + ((*this)[2] * col1)[2];
	float h = ((*this)[2] * col2)[0] + ((*this)[2] * col2)[1] + ((*this)[2] * col2)[2];
	float i = ((*this)[2] * col3)[0] + ((*this)[2] * col3)[1] + ((*this)[2] * col3)[2];

	return Mat3(a , b , c , d , e , f , g , h , i);
}

// Matrix by float multiplication
Mat3 Mat3::operator*(float scalar)
{
	return Mat3((*this)[0] * scalar, (*this)[1] * scalar, (*this)[2] * scalar);
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

// Print the values of the matrix
std::ostream& operator<<(std::ostream& os, const Mat3& mat)
{
	Mat3 mat1 = mat; // We have to make a copy then (cannot access a const)
	os << mat1[0][0] << " , " << mat1[0][1] << " , " << mat1[0][2] << "\n" << mat1[1][0] << " , "
		<< mat1[1][1] << " , " << mat1[1][2] << "\n" << mat1[2][0] << " , " << mat1[2][1] << " , "
		<< mat1[2][2];
	return os;
}