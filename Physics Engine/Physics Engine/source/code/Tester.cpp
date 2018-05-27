/*
	Author: Mohamed Kazma
	Description: This is a tester piece of source code
*/

#include <iostream>
#include "../headers/Vector3D.h"
#include "../headers/Mat3.h"

int main()
{
	// Testing vector3ds
	Vector3D vec1 = Vector3D(0,0,0);
	Vector3D vec2 = Vector3D(1,2,3);
	Vector3D vec3 = Vector3D(-1,2,0);
	Vector3D vec4 = Vector3D(-3,-4,-4);
	
	std::cout << vec1 << std::endl << std::endl;
	std::cout << vec2 << std::endl << std::endl;
	std::cout << vec3 << std::endl << std::endl;
	std::cout << vec4 << std::endl << std::endl;


	// Testing Mat3
	Mat3 mat1 = Mat3(vec1 , vec2 , vec3);
	Mat3 mat2 = Mat3(vec1.x , vec1.y , vec1.z , vec2.x , vec2.y , vec2.z , vec3.x , vec3.y , vec3.z);

	std::cout << mat1 << std::endl << std::endl;
	std::cout << mat2 << std::endl << std::endl;


	//just to hold the console open in vs studio
	std::cin.get();
	return 0;
}