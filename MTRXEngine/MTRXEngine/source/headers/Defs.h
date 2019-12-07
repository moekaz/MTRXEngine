#pragma once

namespace mtrx
{
	#define SQR(x) ((x) * (x)) // Easy way of squaring
	#define CUBE(x) ((x) * (x) * (x)) // Easy macro for cubing

	#define LOGGER_FILE_SIZE 5242880 // Maximum size of logger file 
	#define PI 3.14159265358f // Approximation of pi
	#define PHYSICS_TIMESTEP 0.01666666666f // 60fps timestep
	#define MAX_RAY_SIZE 10000.f

	static float gravity = 9.81f; // Constant value for gravity (not realistic value but games don't have realistic gravity
	static std::string projectDir = std::filesystem::current_path().string(); // Gives us the project dir

	static const glm::vec3 worldUp = glm::vec3(0.f, 1.f, 0.f);
	static const glm::vec3 worldSide = glm::vec3(1.f, 0.f, 0.f);
	static const glm::vec3 worldForward = glm::vec3(0.f, 0.f, -1.f);

	/**
	 * @enum mtrx::ColliderType 
	 * 
	 * @brief Type of colliders that are supported in the engine 
	 * 
	 */
	enum class ColliderType : char { Sphere, AABB, OOBB, Capsule, ConvexShape, };

	/**
	 * @brief The axes that define an objects world
	 * 
	 */
	struct ObjectAxes
	{
		union
		{
			struct
			{
				glm::vec3 side;
				glm::vec3 up;
				glm::vec3 forward;
			};

			glm::vec3 axes[3];
		};

		inline glm::vec3& operator[](int index) { return axes[index]; }
		inline const glm::vec3& operator[](int index) const { return axes[index]; }
		ObjectAxes(const glm::vec3& forward = glm::vec3(0, 0, -1), const glm::vec3& up = glm::vec3(0, 1, 0), const glm::vec3& side = glm::vec3(1, 0, 0)) : 
			forward(forward), side(side), up(up)
		{}
	};
	
	/**
	 * @brief Simplest shape that can encapsulate a point in 3d space
	 * Used within GJK collision detection algorithm
	 * 
	 */
	struct Simplex
	{
		glm::vec3 b;
		glm::vec3 c;
		glm::vec3 d;
		unsigned int size;
	};

	/**
	 * @brief Struct for storing a triangle
	 * 
	 */
	struct Triangle
	{
		union
		{
			struct
			{
				glm::vec3* a;
				glm::vec3* b;
				glm::vec3* c;
			};

			glm::vec3* pts[3];
		};

		Triangle() : a(nullptr), b(nullptr), c(nullptr) {}
		Triangle(glm::vec3* a, glm::vec3* b, glm::vec3* c) : a(a), b(b), c(c) {}
	};

	/**
	 * @brief Generating a random integer between 2 integer values 
	 * 
	 * 
	 * @param min Minimum integer value (inclusive)
	 * @param max Maximum integer value (exclusive)
	 * @return int A random integer within the range of min and max
	 */
	static int RandomInt(int min, int max)
	{
		return rand() % (max - min) + min;
	}

	/**
	 * @brief Generate a cuboid inertia tensor
	 * 
	 * @param mass Mass of the cuboid
	 * @param extents The extents of the cuboid
	 * @return glm::mat3 The inertia tensor generated 
	 */
	static glm::mat3 GenerateCuboidIT(float mass, float* extents)
	{
		// 1/12 = 0.083333... 
		return glm::mat3(0.0833333333f * mass * (extents[1] * extents[1] + extents[2] * extents[2]), 0.f, 0.f,
			0.f, 0.0833333333f * mass * (extents[0] * extents[0] + extents[2] * extents[2]), 0.f,
			0.f, 0.f, 0.0833333333f * mass * (extents[0] * extents[0] + extents[1] * extents[1]));
	}

	/**
	 * @brief Generate a sphere inertia tensor
	 * 
	 * @param mass The mass of the sphere
	 * @param radius The radius of the sphere
	 * @return glm::mat3 The generated inertia tensor
	 */
	static glm::mat3 GenerateSphereIT(float mass, float radius)
	{
		float diagonal = 0.4f * mass * radius;
		return glm::mat3(diagonal, 0.f, 0.f,
			0.f, diagonal, 0.f,
			0.f, 0.f, diagonal);
	}
}
