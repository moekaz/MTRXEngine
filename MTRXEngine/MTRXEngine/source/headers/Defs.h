/*
	Author: Mohamed Kazma
	Description: Some definitions that are useful
*/

#pragma once

namespace mtrx
{	
	#define LOGGER_FILE_SIZE 5242880 // Maximum size of logger file 
	#define PI 3.14159265358f // Approximation of pi

	static float gravity = 9.81f; // Constant value for gravity (not realistic value but games don't have realistic gravity
	static std::string projectDir = std::filesystem::current_path().string(); // Gives us the project dir
	static std::string shaderDir = projectDir + "/source/Renderer/shaders/";

	// World space vectors That we can use (Maybe we don't want to use this)
	static glm::vec3 worldUp = glm::vec3(0.f, 1.f, 0.f);
	static glm::vec3 worldSide = glm::vec3(1.f, 0.f, 0.f);
	static glm::vec3 worldForward = glm::vec3(0.f, 0.f, -1.f);

	// Supported collider types
	enum class ColliderType : char { Sphere, Box, Capsule, Mesh, ConvexShape, };
	
	// Struct that holds some information about a spring
	struct SpringData
	{
		float stiffness;
		float restLength;

		SpringData(float stiffness, float restLength) : stiffness(stiffness), restLength(restLength) 
		{}
	};

	// Struct that holds properties of a liquid used in the buoyancy generator
	struct LiquidProperties
	{
		float density;
		float volume;

		LiquidProperties(float density, float volume) : density(density), volume(volume) 
		{}
	};

	// Transform struct that holds position orientation and scale
	struct Transform
	{
		glm::vec3 position;
		glm::quat orientation;
		glm::vec3 scale;

		Transform(const glm::vec3& position = glm::vec3(), const glm::quat& quaternion = glm::angleAxis(0.f, worldUp), const glm::vec3& scale = glm::vec3(1, 1, 1)) : 
			position(position), orientation(quaternion), scale(scale)
		{}
	};

	static glm::mat3 GenerateCuboidIT(float mass, float* extents)
	{
		// 1/12 = 0.083333... 
		return glm::mat3(glm::vec3(0.0833333333f * mass * (extents[1] * extents[1] + extents[2] * extents[2])),
			glm::vec3(0.0833333333f * mass * (extents[0] * extents[0] + extents[2] * extents[2])),
			glm::vec3(0.0833333333f * mass * (extents[0] * extents[0] + extents[1] * extents[1])));
	}

	// More inertia tensors TBA 
}
