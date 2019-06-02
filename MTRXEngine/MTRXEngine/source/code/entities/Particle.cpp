#include <PrecompiledHeader.h>
#include <entities/Particle.h>

namespace mtrx
{
	Particle::Particle(const glm::vec3& position, const float inverseMass) : Body(position, inverseMass) 
	{}

	Particle::~Particle()
	{}

	void Particle::PhysicsUpdate()
	{
		// If we have an inverseMass of 0 we should not be updating
		if (inverseMass <= 0)
			return;

		// Update acceleration using newton's second law
		acceleration = accumForces * inverseMass;

		// If we use a damping force generator we can set damping to somewhere around 1
		// Update the velocity of the particle using its acceleration and add some damping (maybe use pow on the drag it is much slower)
		//velocity = velocity * pow(damping, GameTime::deltaTime) + acceleration * GameTime::deltaTime;
		velocity = velocity * linearDamping + acceleration * GameTime::deltaTime;

		// Update the position of the particle using its velocity and acceleration (acceleration is not necessary)
		//position += velocity * GameTime::deltaTime + acceleration * GameTime::deltaTime * GameTime::deltaTime * 0.5f;
		position += velocity * GameTime::deltaTime;
		
		// Clear the accumulators
		ClearAccumulators();
	}

	void Particle::ClearAccumulators()
	{
		accumForces.x = 0;
		accumForces.y = 0;
		accumForces.z = 0;
	}
}