/*
	Author: Mohamed Kazma
	Description: Cpp implementation of a 3x3 matrix
*/

#include <PrecompiledHeader.h>
#include <Mat3.h>

namespace MTRX
{
	// Constructor
	Mat3::Mat3(const Vector3D& col1, const Vector3D& col2, const Vector3D& col3)
	{
		matrix[0] = col1;
		matrix[1] = col2;
		matrix[2] = col3;
	}

	// Constructor
	Mat3::Mat3(float a, float b, float c, float d, float e, float f, float g, float h, float i)
	{
		matrix[0] = Vector3D(a, b, c);
		matrix[1] = Vector3D(d, e, f);
		matrix[2] = Vector3D(g, h, i);
	}

	// Destructor
	Mat3::~Mat3() {}

	/* Functions */

	// Inverse of this 3x3 matrix
	Mat3 Mat3::InverseMatrix()
	{
		if (Determinant() != 0) return AdjugateMatrix() * (1 / Determinant());
		else return NULL;
	}

	// Finding the transpose of this 3x3 matrix
	Mat3 Mat3::Transpose()
	{
		Vector3D col1 = Vector3D(matrix[0][0], matrix[1][0], matrix[2][0]);
		Vector3D col2 = Vector3D(matrix[0][1], matrix[1][1], matrix[2][1]);
		Vector3D col3 = Vector3D(matrix[0][2], matrix[1][2], matrix[2][2]);

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

		return Mat3(a, -b, c, -d, e, -f, g, -h, i);
	}

	/* Operator overloading */

	// Return a certain column of the matrix
	Vector3D& Mat3::operator[](int index)
	{
		if (index < 0 || index > 2) throw std::out_of_range("shit just broke");
		return matrix[index];
	}

	const Vector3D& Mat3::operator[](int index) const
	{
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

		return Mat3(a, b, c, d, e, f, g, h, i);
	}

	// Matrix by float multiplication
	Mat3 Mat3::operator*(float scalar)
	{
		return Mat3((*this)[0] * scalar, (*this)[1] * scalar, (*this)[2] * scalar);
	}

	// Matrix += addition
	Mat3 Mat3::operator+=(const Mat3& mat)
	{
		*this = *this + mat;
		return *this;
	}

	// Matrix -= subtraction
	Mat3 Mat3::operator-=(const Mat3& mat)
	{
		*this = *this - mat;
		return *this;
	}

	// Matrix *= multiplication
	Mat3 Mat3::operator*=(const Mat3& mat)
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

	// Print the values of the matrix
	std::ostream& operator<<(std::ostream& os, const Mat3& mat)
	{
		os << mat[0][0] << " , " << mat[0][1] << " , " << mat[0][2] << "\n" << mat[1][0] << " , "
			<< mat[1][1] << " , " << mat[1][2] << "\n" << mat[2][0] << " , " << mat[2][1] << " , "
			<< mat[2][2];
		return os;
	}
}