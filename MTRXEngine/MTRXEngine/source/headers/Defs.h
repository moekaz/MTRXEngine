#pragma once

namespace mtrx
{	
	#define SQR(x) x * x // Easy way of squaring
	#define CUBE(x) x * x * x // Easy macro for cubing

	#define LOGGER_FILE_SIZE 5242880 // Maximum size of logger file 
	#define PI 3.14159265358f // Approximation of pi
	#define WORLD_DIMENSIONS 3 // World dimensions

	static float gravity = 9.81f; // Constant value for gravity (not realistic value but games don't have realistic gravity
	static std::string projectDir = std::filesystem::current_path().string(); // Gives us the project dir

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

	// The axes that define an objects world 
	struct ObjectAxes
	{
		union
		{
			struct
			{
				glm::vec3 forward;
				glm::vec3 up;
				glm::vec3 side;
			};

			glm::vec3 axes[WORLD_DIMENSIONS];
		};


		inline glm::vec3& operator[](int index) { return axes[index]; }
		ObjectAxes(const glm::vec3& forward = glm::vec3(0, 0, -1), const glm::vec3& up = glm::vec3(0, 1, 0), const glm::vec3& side = glm::vec3(1, 0, 0)) : 
			forward(forward), side(side), up(up)
		{}
	};
	
	// Simplest shape that can encapsulate a point in 3d space
	struct Simplex
	{
		glm::vec3* b;
		glm::vec3* c;
		glm::vec3* d;
		unsigned char size;
	};

	// Random int that is inclusive on min and exclusive on max
	static int RandomInt(int min, int max)
	{
		return rand() % (max - min) + min;
	}

	static glm::mat3 GenerateCuboidIT(float mass, float* extents)
	{
		// 1/12 = 0.083333... 
		return glm::mat3(0.0833333333f * mass * (extents[1] * extents[1] + extents[2] * extents[2]), 0.f, 0.f,
			0.f, 0.0833333333f * mass * (extents[0] * extents[0] + extents[2] * extents[2]), 0.f,
			0.f, 0.f, 0.0833333333f * mass * (extents[0] * extents[0] + extents[1] * extents[1]));
	}

	// TBD: Add more inertia tensors TBA 
}
