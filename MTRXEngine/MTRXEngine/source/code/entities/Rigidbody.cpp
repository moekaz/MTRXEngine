/*
	Author: Mohamed Kazma
	Description: Implementation of rigidbodies
*/

#include <PrecompiledHeader.h>
#include <entities/Rigidbody.h>

namespace mtrx
{
	Rigidbody::Rigidbody(float mass, bool isKinematic, const glm::vec3& position, const glm::quat& orientation, const glm::vec3& scale, const glm::mat3& inertiaTensor) : 
		Body(position, orientation, scale, mass), isKinematic(isKinematic), forward(glm::vec3(0, 0, -1)), side(glm::vec3(1, 0, 0)), 
		up(glm::vec3(0, 1, 0)), angularDamping(1.f), inverseInertiaTensor(inertiaTensor), accumTorque(glm::vec3()), objToWorldMat(glm::mat3x4(1.0f)),
		rotation(glm::vec3())
	{}

	Rigidbody::~Rigidbody() {}

	void Rigidbody::PhysicsUpdate()
	{
		// Do not perform physics calculations
		if (isKinematic || GetIsInfiniteMass())
			return;

		// Get acceleration with accumulated forces and inverse mass
		//prevAcceleration = acceleration + inverseMass * accumForces;
		acceleration = accumForces * inverseMass;

		// Get angular acceleration
		glm::vec3 angularAcceleration = accumTorque * inverseInertiaTensor;

		// Integrate the acceleration to get the velocity
		velocity += acceleration * GameTime::deltaTime;

		// Integrate the angular acceleration to get the rotation
		rotation += angularAcceleration * GameTime::deltaTime;

		// Add damping
		velocity *= linearDamping;
		rotation *= angularDamping;

		// Modify position and orientation
		transform.position += velocity * GameTime::deltaTime;
		transform.orientation += 0.5f * transform.orientation * glm::quat(0.f, rotation * GameTime::deltaTime);

		// Calculate the body data from the updated positions
		CalculateBodyData();
		
		// Clear the accumulators
		ClearAccumulators();
	}

	void Rigidbody::ClearAccumulators()
	{
		accumTorque.x = 0;
		accumTorque.y = 0;
		accumTorque.z = 0;
		accumForces.x = 0;
		accumForces.y = 0;
		accumForces.z = 0;
	}

	void Rigidbody::IntegrateRotation()
	{}

	void Rigidbody::AddForceAtPoint(const glm::vec3& force, const glm::vec3& point)
	{
		// Point is assumed to be in world space 
		glm::vec3 pt = point;
		pt -= transform.position;

		accumForces += force;
		accumTorque += glm::cross(pt, force);
	}

	void Rigidbody::CalculateBodyData()
	{
		// Normalize orientation
		glm::normalize(transform.orientation);

		// Calculate the object to world transform
		CalculateObjToWorldMat();
		
		// Calculate inverse inertia tensor in world coordinates
		CalculateIITWorld();
	}
	
	void Rigidbody::CalculateObjToWorldMat()
	{
		// i,j,k -> x,y,z
		objToWorldMat[0][0] = 1 - 2 * transform.orientation.y * transform.orientation.y - 2 * transform.orientation.z * transform.orientation.z;
		objToWorldMat[0][1] = 2 * transform.orientation.x * transform.orientation.y - 2 * transform.orientation.w * transform.orientation.z;
		objToWorldMat[0][2] = 2 * transform.orientation.x * transform.orientation.z + 2 * transform.orientation.w * transform.orientation.y;
		objToWorldMat[0][3] = transform.position.x;
		objToWorldMat[1][0] = 2 * transform.orientation.x * transform.orientation.y + 2 * transform.orientation.w * transform.orientation.z;
		objToWorldMat[1][1] = 1 - 2 * transform.orientation.x * transform.orientation.x - 2 * transform.orientation.z * transform.orientation.z;
		objToWorldMat[1][2] = 2 * transform.orientation.y * transform.orientation.z - 2 * transform.orientation.w * transform.orientation.x;
		objToWorldMat[1][3] = transform.position.y;
		objToWorldMat[2][0] = 2 * transform.orientation.x * transform.orientation.z - 2 * transform.orientation.w * transform.orientation.y;
		objToWorldMat[2][1] = 2 * transform.orientation.y * transform.orientation.z + 2 * transform.orientation.w * transform.orientation.x;
		objToWorldMat[2][2] = 1 - 2 * transform.orientation.x * transform.orientation.x - 2 * transform.orientation.y * transform.orientation.y;
		objToWorldMat[2][3] = transform.position.z;
	}
}