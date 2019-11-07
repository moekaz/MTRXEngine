#include "PrecompiledHeader.h"
#include "FluidSimulationDemo.h"

// Particle Parameters
float radius = 0.2f;
float mass = 1.f;
float restDensity = 20.f;
float K = 20.f; // Pressure constant
float viscosityCoefficient = 0.018f;
float drag = 0.1f;
float smoothingRadius = radius;
float damping = -0.5f;
float maximumVelocity = 75.0f;
float maximumAcceleration = 75.0f;

// Force parameters
float motionDampingCoefficent = 0.0f;
float spikeyGradCoefficient = -45.0 / (PI * pow(smoothingRadius, 6.0));
float viscosityLaplacianCoefficient = 45.0 / (PI * pow(smoothingRadius, 6.0f));
float poly6Coefficient = (315.f / (64.f * PI * pow(smoothingRadius, 9.f)));
float smoothingRadiusSqr = SQR(smoothingRadius);

// Obstacle Parameters
float stuckToBoundaryRadius = 0.01f;
float boundaryDampingCoefficient = 0.6f;
double boundaryForceRadius = 0.1f;
double minBoundaryForce = 0.0;
double maxBoundaryForce = 0.0;
float xMin = 0.f;
float yMin = 0.f;
float zMin = 0.f;
float xMax = 10.f;
float yMax = 10.f;
float zMax = 10.f;

// 
glm::vec3 gravity = glm::vec3(0, -2.f, 0);
bool started = false;

FluidSimulationDemo::FluidSimulationDemo() : Demo("Fluid Simulation Demo", 1280, 720), numParticles(500), startSim(false)
{
	mesh = 2;
	application.camera->GetTransform().SetPosition(glm::vec3(0, 2.f, 40.f));
}

void FluidSimulationDemo::Update()
{
	while (!application.window.ShouldClose())
	{
		// Update Positions
		for (int i = 0; i < particles.size(); ++i)
		{
			colliders[i]->SetPosition(particles[i]->rb->GetPosition());
		}

		// Update the particles
		UpdateParticles();

		// Update delta time
		mtrx::GameTime::Update();

		// Check for opengl errors
		application.PollOpenGlErrors();

		// Basic input checks that will shared by all applications
		BaseInputCheck();
		InputCheck();

		// Update application (includes input checks)
		application.Update(mtrx::GameTime::deltaTime);

		// Clear the window
		application.window.Clear();

		// Update the rigidbody and the particle system
		//rbManager.Integrate(mtrx::GameTime::deltaTime);

		// Update renderer
		application.renderer.Render(transformsToRender, mesh);

		// Update input system
		application.inputSystem->Update();

		// Update the UI layer's frame
		UILayer::UpdateFrame();

		// PS: You want to have all logic and that stuff before this call 
		// Clear buffers and poll
		application.window.UpdateBuffers();
	}
}

void FluidSimulationDemo::InputCheck()
{
	if (!started && application.inputSystem->GetKeyDown(GLFW_KEY_SPACE))
	{
		glm::vec3 startPos(1.f, 4.f, 0);
		float offset = radius * 4.f; // TBD: This should be affected by scale
		float numParticlesDimension = std::ceil(cbrt(numParticles));
		int particlesCreated = 0;

		// Create the particles in a rectangle
		for (int i = 0; i < numParticlesDimension; ++i)
		{
			for (int j = 0; j < numParticlesDimension; ++j)
			{
				for (int k = 0; k < numParticlesDimension; ++k)
				{
					if (particlesCreated >= numParticles)
						break;

					float x = startPos.x + (k * offset);
					float y = startPos.y + (j * offset);
					float z = startPos.z - (i * offset);

					glm::vec3 position(x, y, z);
					glm::quat orientation = glm::angleAxis(0.f, glm::vec3(0, 1, 0));
					glm::vec3 scale(radius, radius, radius);
					glm::mat3 tensor = mtrx::GenerateSphereIT(mass, radius);

					mtrx::Rigidbody* body = new mtrx::Rigidbody(mass, false, position, orientation, scale, tensor);
					mtrx::Collider* collider = new mtrx::SphereCollider(position, orientation, scale, radius);

					body->SetLinearDamping(0.99999f);

					rbManager.AddRigidbody(body);

					transformsToRender.insert(&body->GetTransform());
					particles.push_back(new particle(restDensity, 0, body));
					colliders.push_back(collider);
					++particlesCreated;
				}
			}
		}

		started = true;
	}
}

void FluidSimulationDemo::UpdateParticles()
{	
	// Check if we need to remove some stuck particles (check for stuck particles)
	//RemoveStuckParticles();

	// Update grid
	//UpdateGrid();
	//UpdateNeighbors();

	// Update fluid density and forces
	//ApplyDensity();
	ApplyForces();

	// Update positions
	UpdatePositions();

	// Update obstacle velocity
	//UpdateObstacleVelocity();
}

void FluidSimulationDemo::ApplyDensity()
{
	for (int i = 0; i < particles.size(); ++i)
	{
		for (int j = 0; j < particles.size(); ++j)
		{
			if (i == j)
				continue;

			glm::vec3 diff = particles[j]->rb->GetPosition() - particles[i]->rb->GetPosition();
			float distanceSqr = glm::length2(diff);

			if (distanceSqr >= smoothingRadiusSqr) // Particle is too far away
				continue;

			// p = m * kernel
			float smoothingKernel = poly6Coefficient * CUBE(smoothingRadiusSqr - distanceSqr);
			float density = mass * smoothingKernel;
			particles[i]->density = std::max(density, restDensity); // To avoid negative densities

			// Calculate pressure value
			particles[i]->pressure = K * (particles[i]->density - restDensity);
		}
	}
}

void FluidSimulationDemo::ApplyForces()
{
	particle* p;
	particle* p1;
	for (int i = 0; i < particles.size(); ++i)
	{
		p = particles[i];
		glm::vec3 acceleration = glm::vec3();
		glm::vec3 vdiff = glm::vec3();
		glm::vec3 pressureForce = glm::vec3();
		glm::vec3 viscosityForce = glm::vec3();

		for (int j = 0; j < particles.size(); ++j)
		{
			if (i == j)
				continue;
			
			p1 = particles[j];

			glm::vec3 diff = p->rb->GetPosition() - p1->rb->GetPosition();
			float distance = glm::length(diff);
			float difference = smoothingRadius - distance;

			if (distance == 0 || difference > 0) // If we are too far away or distance is 0  
				continue;
			
			diff = (1 / distance) * diff; // Normalize the vector since we already have the distance
			float spikeyCoefficient = spikeyGradCoefficient * SQR(difference);
			float massRatio = p1->rb->GetMass() / p->rb->GetMass();
			float pTerm = (p->pressure + p1->pressure) / (2 * p->density * p1->density);
			acceleration -= massRatio * pTerm * spikeyCoefficient * diff;

			// Viscosity
			float laplacian = viscosityLaplacianCoefficient * difference;
			vdiff = p1->rb->GetVelocity() - p->rb->GetVelocity();
			acceleration += viscosityCoefficient * massRatio * ((1.f / p1->density) * laplacian) * vdiff; // Is this vdiff
		}

		acceleration += gravity;
		//acceleration += BarrierCollisionCorrection(p); // Some collision correction due to the barriers of the simulation

		// MIGHT NEED TO DO THAT FIRST 
		// Motion damping (we can do this later on)
		float magSqr = glm::length2(acceleration);
		if (magSqr > 50)
			acceleration = 50.f * glm::normalize(acceleration);

		p->rb->SetAcceleration(acceleration);
	}
}

void FluidSimulationDemo::UpdatePositions()
{
	for (int i = 0; i < particles.size(); ++i)
	{
		particle* p = particles[i];

		p->rb->GetVelocity() += mtrx::GameTime::deltaTime * p->rb->GetAcceleration();
		float magSqr = glm::length2(p->rb->GetVelocity());
		if (magSqr > 50.f)
			p->rb->SetVelocity(50.f * p->rb->GetVelocity());

		p->rb->GetPosition() += mtrx::GameTime::deltaTime * p->rb->GetVelocity();

		CollisionPositionCorrection(p);
	}
}

glm::vec3 FluidSimulationDemo::BarrierCollisionCorrection(particle* part)
{
	double r = boundaryForceRadius;
	double minf = minBoundaryForce;
	double maxf = maxBoundaryForce;

	glm::vec3& p = part->rb->GetPosition();
	glm::vec3 acceleration = glm::vec3(0.0, 0.0, 0.0);
	float mass = part->rb->GetMass();

	// Are these maxes and mins fine??
	if (p.x < xMin + r)
	{
		double dist = fmax(0.0, p.x - xMin);
		double force = lerp(maxf, minf, dist / r);
		acceleration += glm::vec3(force / mass, 0.0, 0.0);
	}
	else if (p.x > xMax - r)
	{
		double dist = fmax(0.0, xMax - p.x);
		double force = lerp(maxf, minf, dist / r);
		acceleration += glm::vec3(-force / mass, 0.0, 0.0);
	}

	if (p.y < yMin + r)
	{
		double dist = fmax(0.0, p.y - yMin);
		double force = lerp(maxf, minf, dist / r);
		acceleration += glm::vec3(0.0, force / mass, 0.0);
	}
	else if (p.y > yMax - r) {
		double dist = fmax(0.0, yMax - p.y);
		double force = lerp(maxf, minf, dist / r);
		acceleration += glm::vec3(0.0, -force / mass, 0.0);
	}

	if (p.z < zMin + r)
	{
		double dist = fmax(0.0, p.z - zMin);
		double force = lerp(maxf, minf, dist / r);
		acceleration += glm::vec3(0.0, 0.0, force / mass);
	}
	else if (p.z > zMax - r) {
		double dist = fmax(0.0, zMax - p.z);
		double force = lerp(maxf, minf, dist / r);
		acceleration += glm::vec3(0.0, 0.0, -force / mass);
	}

	return acceleration;
}

void FluidSimulationDemo::CollisionPositionCorrection(particle* part)
{
	double eps = 0.001;
	float d = boundaryDampingCoefficient;
	glm::vec3& p = part->rb->GetPosition();
	glm::vec3& vel = part->rb->GetVelocity();

	if (p.x < xMin) 
	{
		part->rb->SetPosition(glm::vec3(xMin + eps, p.y, p.z));
		part->rb->SetVelocity(glm::vec3(-d * vel.x, vel.y, vel.z));
	}
	else if (p.x > xMax) 
	{
		part->rb->SetPosition(glm::vec3(xMax - eps, p.y, p.z));
		part->rb->SetVelocity(glm::vec3(-d * vel.x, vel.y, vel.z));
	}

	if (p.y < yMin)
	{
		part->rb->SetPosition(glm::vec3(p.x, yMin + eps, p.z));
		part->rb->SetVelocity(glm::vec3(vel.x, -d * vel.y, vel.z));
	}
	else if (p.y > yMax) 
	{
		part->rb->SetPosition(glm::vec3(p.x, yMax - eps, p.z));
		part->rb->SetVelocity(glm::vec3(vel.x, -d * vel.y, vel.z));
	}

	if (p.z < zMin) 
	{
		part->rb->SetPosition(glm::vec3(p.x, p.y, zMin + eps));
		part->rb->SetVelocity(glm::vec3(vel.x, vel.y, -d * vel.z));
	}
	else if (p.z > zMax) 
	{
		part->rb->SetPosition(glm::vec3(p.x, p.y, zMax - eps));
		part->rb->SetVelocity(glm::vec3(vel.x, vel.y, -d * vel.z));
	}
}

void FluidSimulationDemo::PrintPositions()
{
	for (auto iter = particles.begin(); iter != particles.end(); ++iter)
	{
		glm::vec3& pos = (*iter)->rb->GetPosition();
		std::cout << pos.x << " " << pos.y << " " << pos.z << std::endl;
	}
}

/*bool FluidSimulationDemo::isFluidParticleStuckToBoundary(particle* part) {
	double r = stuckToBoundaryRadius;
	bool isStuck = false;
	glm::vec3& p = part->position;

	// Needs to be redone
	if (p.x < xmin + r || p.x > xmax - r ||
		p.y < ymin + r || p.y > ymax - r ||
		p.z < zmin + r || p.z > zmax - r) {
		isStuck = true;
	}

	return isStuck;
}*/

void FluidSimulationDemo::RemoveStuckParticles()
{

}

void FluidSimulationDemo::UpdateGrid()
{

}

void FluidSimulationDemo::UpdateNeighbors()
{

}

void FluidSimulationDemo::UpdateObstacleVelocity()
{

}
