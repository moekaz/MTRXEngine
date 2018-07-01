/*
	Author: Mohamed Kazma
	Description: This is a tester piece of source code
*/

#include <iostream>
#include "../headers/Vector3D.h"
#include "../headers/Mat3.h"
#include "../headers/SphereCollider.h"

// Testing 3d vectors
void VectorTesting()
{
	// Testing vector3Ds
	Vector3D vec1 = Vector3D(0, 0, 0);
	Vector3D vec2 = Vector3D(1, 2, 3);
	Vector3D vec3 = Vector3D(-1, 2, 0);
	Vector3D vec4 = Vector3D(-3, -4, -4);

	// Testing initial values
	std::cout << "Testing the values of the vectors:" << std::endl;
	std::cout << "----------------------------------" << std::endl << std::endl;

	std::cout << vec1 << std::endl << std::endl;
	std::cout << vec2 << std::endl << std::endl;
	std::cout << vec3 << std::endl << std::endl;
	std::cout << vec4 << std::endl << std::endl;

	// Testing vector functions
	std::cout << "Testing the vector functions:" << std::endl;
	std::cout << "-----------------------------" << std::endl << std::endl;

	std::cout << "Vector Magnitude:" << std::endl << std::endl;

	std::cout << vec1.Magnitude() << std::endl;
	std::cout << vec2.Magnitude() << std::endl;
	std::cout << vec3.Magnitude() << std::endl;
	std::cout << vec4.Magnitude() << std::endl << std::endl;

	std::cout << "Vector Magnitude Squared:" << std::endl << std::endl;

	std::cout << vec1.MagnitudeSquared() << std::endl;
	std::cout << vec2.MagnitudeSquared() << std::endl;
	std::cout << vec3.MagnitudeSquared() << std::endl;
	std::cout << vec4.MagnitudeSquared() << std::endl << std::endl;

	std::cout << "Vector Dot Product:" << std::endl << std::endl;

	std::cout << vec1.DotProduct(vec2) << std::endl;
	std::cout << vec2.DotProduct(vec3) << std::endl;
	std::cout << vec3.DotProduct(vec4) << std::endl;
	std::cout << vec4.DotProduct(vec1) << std::endl << std::endl;

	std::cout << "Vector Cross Product:" << std::endl << std::endl;

	std::cout << vec1.CrossProduct(vec2) << std::endl << std::endl;
	std::cout << vec2.CrossProduct(vec3) << std::endl << std::endl;
	std::cout << vec3.CrossProduct(vec4) << std::endl << std::endl;
	std::cout << vec4.CrossProduct(vec1) << std::endl << std::endl;

	std::cout << "Vector Normalize: " << std::endl << std::endl;

	std::cout << vec1.Normalize() << std::endl << std::endl;
	std::cout << vec2.Normalize() << std::endl << std::endl;
	std::cout << vec3.Normalize() << std::endl << std::endl;
	std::cout << vec4.Normalize() << std::endl << std::endl;

	std::cout << "Vector Magnitude:" << std::endl;

	std::cout << vec1.Magnitude() << std::endl;
	std::cout << vec2.Magnitude() << std::endl;
	std::cout << vec3.Magnitude() << std::endl;
	std::cout << vec4.Magnitude() << std::endl << std::endl;


	// Testing vector operator overloads
	std::cout << "Printing out initial values of the vectors:" << std::endl;
	std::cout << "------------------------------------------" << std::endl << std::endl;

	std::cout << vec1 << std::endl << std::endl;
	std::cout << vec2 << std::endl << std::endl;
	std::cout << vec3 << std::endl << std::endl;
	std::cout << vec4 << std::endl << std::endl;

	std::cout << "Vector Difference:" << std::endl << std::endl;

	std::cout << vec1 - vec2 << std::endl << std::endl;
	std::cout << vec2 - vec1 << std::endl << std::endl;
	std::cout << vec3 - vec4 << std::endl << std::endl;
	std::cout << vec4 - vec3 << std::endl << std::endl;

	std::cout << "Vector Difference with floats: " << std::endl << std::endl;

	std::cout << vec1 - 3 << std::endl << std::endl;
	std::cout << vec2 - 3 << std::endl << std::endl;
	std::cout << vec3 - 3 << std::endl << std::endl;
	std::cout << vec4 - 3 << std::endl << std::endl;

	std::cout << vec1 - -2 << std::endl << std::endl;
	std::cout << vec2 - -2 << std::endl << std::endl;
	std::cout << vec3 - -2 << std::endl << std::endl;
	std::cout << vec4 - -2 << std::endl << std::endl;

	std::cout << "Vector Addition: " << std::endl << std::endl;

	std::cout << vec1 + vec2 << std::endl << std::endl;
	std::cout << vec2 + vec3 << std::endl << std::endl;
	std::cout << vec3 + vec4 << std::endl << std::endl;
	std::cout << vec4 + vec1 << std::endl << std::endl;

	std::cout << "Vector Addition with floats: " << std::endl << std::endl;

	std::cout << vec1 + 3 << std::endl << std::endl;
	std::cout << vec2 + 3 << std::endl << std::endl;
	std::cout << vec3 + 3 << std::endl << std::endl;
	std::cout << vec4 + 3 << std::endl << std::endl;

	std::cout << vec1 + -2 << std::endl << std::endl;
	std::cout << vec2 + -2 << std::endl << std::endl;
	std::cout << vec3 + -2 << std::endl << std::endl;
	std::cout << vec4 + -2 << std::endl << std::endl;

	std::cout << "Vector Multiplication:" << std::endl << std::endl;

	std::cout << vec1 * vec2 << std::endl << std::endl;
	std::cout << vec2 * vec3 << std::endl << std::endl;
	std::cout << vec3 * vec4 << std::endl << std::endl;
	std::cout << vec4 * vec1 << std::endl << std::endl;

	std::cout << "Vector Multiplication with floats:" << std::endl << std::endl;

	std::cout << vec1 * 3 << std::endl << std::endl;
	std::cout << vec2 * 3 << std::endl << std::endl;
	std::cout << vec3 * 3 << std::endl << std::endl;
	std::cout << vec4 * 3 << std::endl << std::endl;

	std::cout << vec1 * -2 << std::endl << std::endl;
	std::cout << vec2 * -2 << std::endl << std::endl;
	std::cout << vec3 * -2 << std::endl << std::endl;
	std::cout << vec4 * -2 << std::endl << std::endl;
}

// Testing 3x3 matrices
void MatrixTesting()
{
	// Testing Mat3
	Mat3 mat1 = Mat3(Vector3D(1 , 7 , 5) ,  Vector3D(-5 , 4 , 8) , Vector3D(10 , -2 , 2));
	Mat3 mat2 = Mat3(6 , 4 , 7 , -1 , -5 , 5 , 7 , 10 , 1);

	std::cout << "Testing 3x3 matrices: " << std::endl;
	std::cout << "---------------------" << std::endl << std::endl;

	// Printing out original matrix values
	std::cout << mat1 << std::endl << std::endl;
	std::cout << mat2 << std::endl << std::endl;

	/* Testing Functions */

	// Inverse of a 3x3 matrix
	std::cout << "Inverse of 3x3 matrices: " << std::endl << std::endl;

	std::cout << mat1.InverseMatrix() << std::endl << std::endl;
	std::cout << mat2.InverseMatrix() << std::endl << std::endl;

	// Transpose of a 3x3 matrix
	std::cout << "Transpose of a 3x3 matrices: " << std::endl << std::endl;

	std::cout << mat1.Transpose() << std::endl << std::endl;
	std::cout << mat2.Transpose() << std::endl << std::endl;

	// Adjugate of a 3x3 matrix
	std::cout << "Adjugate of a 3x3 matrices: " << std::endl << std::endl;

	std::cout << mat1.AdjugateMatrix() << std::endl << std::endl;
	std::cout << mat2.AdjugateMatrix() << std::endl << std::endl;

	// Determinant of a 3x3 matrix
	std::cout << "Determinant 3x3 matrices: " << std::endl << std::endl;

	std::cout << mat1.Determinant() << std::endl << std::endl;
	std::cout << mat2.Determinant() << std::endl << std::endl;

	/* Testing Operator Overloads */

	// Adding matrices
	std::cout << "Adding 3x3 matrices: " << std::endl << std::endl;

	std::cout << mat1 + mat2 << std::endl << std::endl;
	std::cout << mat2 + mat1 << std::endl << std::endl;

	// Subtracting matrices
	std::cout << "Subtracting 3x3 matrices: " << std::endl << std::endl;

	std::cout << mat1 - mat2 << std::endl << std::endl;
	std::cout << mat2 - mat1 << std::endl << std::endl;

	// Multiplying matrices
	std::cout << "Multiplying 3x3 matrices: " << std::endl << std::endl;

	std::cout << mat1 * mat2 << std::endl << std::endl;
	std::cout << mat2 * mat1 << std::endl << std::endl;

	// Multiplying a matrix by a float
	std::cout << "Multiplying 3x3 matrix by a float: " << std::endl << std::endl;

	std::cout << mat1 * 5 << std::endl << std::endl;
	std::cout << mat2 * -4 << std::endl << std::endl;

	std::cout << "Dividing 3x3 matrices: " << std::endl << std::endl;

	std::cout << mat1 / mat2 << std::endl << std::endl;
	std::cout << mat2 / mat1 << std::endl << std::endl;
}

void SphereColliderTesting()
{
	int i = 300;
	SphereCollider collider1 = SphereCollider();
	SphereCollider collider2 = SphereCollider(Vector3D(30,0,0));

	while (i > 0)
	{
		collider2.Update(collider2.center - Vector3D(1,0,0));
		std::cout << collider2.CheckCollision(collider1) << std::endl;
		i--;
	}
}

int main()
{
	// Testing classes
	VectorTesting();
	MatrixTesting();
	SphereColliderTesting();

	//just to hold the console open in vs studio
	while (true) {}
	return 0;
}

