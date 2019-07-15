/*
	Author: Mohamed Kazma
	Description: This is a tester piece of source code
*/

#include <PrecompiledHeader.h>
#include <math/Vector3D.h>
#include <math/Mat3.h>
#include <colliders/SphereCollider.h>
#include <colliders/BoxCollider.h>
#include <colliders/CapsuleCollider.h>
#include <colliders/ConvexShapeCollider.h>
#include <utils/PhysicsUtil.h>
#include <log/LogManager.h>

// HOW AM I CHECKING FOR MEMORY LEAKS

// Testing 3d vectors
void VectorTesting()
{
	
	// Testing vector3Ds
	mtrx::Vector3D vec1 = mtrx::Vector3D(0, 0, 0);
	mtrx::Vector3D vec2 = mtrx::Vector3D(1, 2, 3);
	mtrx::Vector3D vec3 = mtrx::Vector3D(-1, 2, 0);
	mtrx::Vector3D vec4 = mtrx::Vector3D(-3, -4, -4);

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
	mtrx::Mat3 mat1 = mtrx::Mat3(mtrx::Vector3D(1 , 7 , 5) , mtrx::Vector3D(-5 , 4 , 8) , mtrx::Vector3D(10 , -2 , 2));
	mtrx::Mat3 mat2 = mtrx::Mat3(6 , 4 , 7 , -1 , -5 , 5 , 7 , 10 , 1);


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

	//std::cout << mat1 / mat2 << std::endl << std::endl;
	//std::cout << mat2 / mat1 << std::endl << std::endl;
}

void SphereColliderTesting()
{
	int i = 300;
	mtrx::SphereCollider collider1 = mtrx::SphereCollider();
	mtrx::SphereCollider collider2 = mtrx::SphereCollider(glm::vec3(30,0,0));

	//std::cout << collider1 << std::endl;

	std::vector<glm::vec3*> vertices1 = 
	{ 
		new glm::vec3(4 , 11 , 0), 
		new glm::vec3(4 , 6.81818175, 0),
		new glm::vec3(9 , 9 , 0),
	};

	std::vector<glm::vec3*> vertices2 = 
	{
		new glm::vec3(5 , 7 , 0),
		new glm::vec3(7 , 3 , 0),
		new glm::vec3(10 , 2 , 0),
		new glm::vec3(12 , 7 , 0)
	};

	mtrx::ConvexShapeCollider col1 = mtrx::ConvexShapeCollider();
	mtrx::ConvexShapeCollider col2 = mtrx::ConvexShapeCollider();
	col1.vertices = vertices1;
	col2.vertices = vertices2;

	/*
	for (int i = 0; i < 10000; i++)
	{
		col1.CheckCollision(col2);
	}
	*/

	std::cout << "Collision of convex shapes: " << col1.CheckCollision(col2) << std::endl;

	/*
	glm::vec3 A = glm::vec3(0, 0, 0);
	glm::vec3 B = glm::vec3(1, 0, 0);
	glm::vec3 C = glm::vec3(0, 1, 0);
	glm::vec3 D = glm::vec3(1, 1, 0);

	std::cout << PhysicsUtil::MinDistanceSquaredTwoSegments(A, B, C, D) << std::endl;
	*/

	//C = glm::vec3(0.5, 2, 0);
	//std::cout << "Distance between point and line segment: " << PhysicsUtil::MinDistanceSquaredPointSegment(A, B, C , D) << std::endl;

	glm::vec3 center = glm::vec3(0, 2.0f, 0);
	mtrx::CapsuleCollider cap1 = mtrx::CapsuleCollider();
	mtrx::CapsuleCollider cap2 = mtrx::CapsuleCollider(center);

	std::cout << "Capsule capsule Collision: " << cap1.CheckCollision(cap2) << std::endl;

	mtrx::BoxCollider b = mtrx::BoxCollider(glm::vec3(0, 0 ,0));

	std::cout << "Sphere box collision detection: " << collider1.CheckCollision(b) << std::endl;

	/*
	while (i > 0)
	{
		std::cout << "i: " << i << std::endl;
		collider2.Update(collider2.center - glm::vec3(1,0,0));
		std::cout << "Collider1: " << std::endl <<  collider1 << std::endl;
		std::cout << "Collider2: " << std::endl << collider2 << std::endl;
		std::cout << "COLLISION: " << collider2.CheckCollision(collider1) << std::endl;


		std::cout << std::endl;	// Separating line
		i--;
	}
	*/
	// Delete the vertices
}

//int main()
//{
//	mtrx::LogManager::init();
//	MTRX_WARN("hello initialized logger");
//	MTRX_INFO("INFO!!!");
//	MTRX_TRACE("INFO!!!");
//	MTRX_ERROR("INFO!!!");
//	MTRX_CRITICAL("INFO!!!");
//
//	// Testing classes
//	VectorTesting();
//	MatrixTesting();
//	SphereColliderTesting();
//
//	// Just to hold the console open in vs
//	std::string input;
//	getline(std::cin, input);
//	return 0;
//}

