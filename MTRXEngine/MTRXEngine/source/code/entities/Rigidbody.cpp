/*
	Author: Mohamed Kazma
	Description: Implementation of rigidbodies
*/

#include <PrecompiledHeader.h>
#include <entities/Rigidbody.h>

namespace mtrx
{
	Rigidbody::Rigidbody(float mass, bool isKinematic, const glm::vec3& position, const glm::quat& orientation, const glm::vec3& scale, const glm::mat3& inertiaTensor) : 
		Body(position, orientation, scale, mass), isKinematic(isKinematic), axes(glm::vec3(0, 0, -1), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0)),
		angularDamping(1.f), accumTorque(glm::vec3()), rotation(glm::vec3())
	{
		SetInverseInertiaTensor(inertiaTensor);
		CalculateObjToWorldMat();
	}

	Rigidbody::~Rigidbody() {}

	void Rigidbody::Integrate(float deltaTime)
	{
		// Do not perform physics calculations
		if (isKinematic || GetIsInfiniteMass())
			return;

		// Get acceleration with accumulated forces and inverse mass
		acceleration = accumForces * inverseMass;

		// Get angular acceleration
		glm::vec3 angularAcceleration = accumTorque * CalculateIITWorld();

		// Integrate the acceleration to get the velocity
		velocity += acceleration * deltaTime;

		// Integrate the angular acceleration to get the rotation
		rotation += angularAcceleration * deltaTime;

		// Add damping
		velocity *= linearDamping;
		rotation *= angularDamping;

		// Modify position and orientation
		transform.Translate(velocity * deltaTime);
		transform.GetOrientation() += 0.5f * transform.GetOrientation() * glm::quat(0.f, rotation * deltaTime);

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

	void Rigidbody::SetInverseInertiaTensor(const glm::mat3& inertiaTensor)
	{
		inverseInertiaTensor[0][0] = 1.f / inertiaTensor[0][0];
		inverseInertiaTensor[0][1] = 0;
		inverseInertiaTensor[0][2] = 0;
		inverseInertiaTensor[1][0] = 0;
		inverseInertiaTensor[1][1] = 1.f / inertiaTensor[1][1];
		inverseInertiaTensor[1][2] = 0;
		inverseInertiaTensor[2][0] = 0;
		inverseInertiaTensor[2][1] = 0;
		inverseInertiaTensor[2][2] = 1.f / inertiaTensor[2][2];
	}

	void Rigidbody::AddForceAtPoint(const glm::vec3& force, const glm::vec3& point)
	{
		// Point is assumed to be in world space 
		glm::vec3 pt = point;
		pt -= transform.GetPosition();

		accumForces += force;
		accumTorque += glm::cross(pt, force);
	}

	void Rigidbody::CalculateBodyData()
	{
		// Normalize orientation
		transform.SetOrientation(glm::normalize(transform.GetOrientation()));

		// Calculate the object to world transform
		CalculateObjToWorldMat();
	}
	
	void Rigidbody::CalculateObjToWorldMat()
	{
		glm::quat& orientation = transform.GetOrientation();
		glm::vec3& position = transform.GetPosition();

		// i,j,k -> x,y,z
		objToWorldMat[0][0] = 1 - 2 * orientation.y * orientation.y - 2 * orientation.z * orientation.z;
		objToWorldMat[0][1] = 2 * orientation.x * orientation.y - 2 * orientation.w * orientation.z;
		objToWorldMat[0][2] = 2 * orientation.x * orientation.z + 2 * orientation.w * orientation.y;
		objToWorldMat[0][3] = position.x;
		objToWorldMat[1][0] = 2 * orientation.x * orientation.y + 2 * orientation.w * orientation.z;
		objToWorldMat[1][1] = 1 - 2 * orientation.x * orientation.x - 2 * orientation.z * orientation.z;
		objToWorldMat[1][2] = 2 * orientation.y * orientation.z - 2 * orientation.w * orientation.x;
		objToWorldMat[1][3] = position.y;
		objToWorldMat[2][0] = 2 * orientation.x * orientation.z - 2 * orientation.w * orientation.y;
		objToWorldMat[2][1] = 2 * orientation.y * orientation.z + 2 * orientation.w * orientation.x;
		objToWorldMat[2][2] = 1 - 2 * orientation.x * orientation.x - 2 * orientation.y * orientation.y;
		objToWorldMat[2][3] = position.z;
	}
}