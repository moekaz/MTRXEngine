#include "PrecompiledHeader.h"
#include "FluidSimulationDemo.h"

// Particle Parameters
float radius = 0.02f;
float smoothingRadius = 0.2f;
float smoothingRadiusSqr = SQR(smoothingRadius);
int numParticles = 1500;

float mass = 1.f;
float restDensity = 20.f;
float K = 20.f; // Pressure constant
float viscosityCoefficient = 0.018f;

float maximumVelocity = 75.0f;
float maximumAcceleration = 75.0f;
float maximumAccelerationSqr = SQR(75.0f);
float maximumVelocitySqr = SQR(75.0f);

// Force parameters
float spikeyGradCoefficient = -45.f / (PI * pow(smoothingRadius, 6.f));
float viscosityLaplacianCoefficient = 45.f / (PI * pow(smoothingRadius, 6.f));
float poly6Coefficient = (315.f / (64.f * PI * pow(smoothingRadius, 9.f)));

// Obstacle Parameters
float boundaryDampingCoefficient = 0.75f;
float boundaryForceRadius = 0.1f;
float minBoundaryForce = 0.f;
float maxBoundaryForce = 0.f;

float xMin = -2.5f;
float yMin = -2.5f;
float zMin = -2.5f;
float xMax = 2.5f;
float yMax = 6.f;
float zMax = -1.f;

float courantSafetyFactor = 1.0f;
float minTimeStep = (float)(1.0 / 240.0);

// 
glm::vec3 gravity = glm::vec3(0, -9.8f, 0);
bool started = false;

float InvSqrt(float x) 
{
	float xhalf = 0.5f * x;
	int i = *(int*)&x;            // store floating-point bits in integer
	i = 0x5f3759df - (i >> 1);    // initial guess for Newton's method
	x = *(float*)&i;              // convert new bits into float
	x = x * (1.5f - xhalf * x * x);     // One round of Newton's method
	return x;
}

FluidSimulationDemo::FluidSimulationDemo() : Demo("Fluid Simulation Demo", 1280, 720)
{
	mesh = 2;
	application.camera->GetTransform().SetPosition(glm::vec3(0.f, 2.f, 10.f));
	//application.camera->GetTransform().Rotate(glm::angleAxis(-180.f, glm::vec3(0, 1, 0)));
	//application.window.SetVsync(true);
}

void FluidSimulationDemo::Update()
{
	while (!application.window.ShouldClose())
	{
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

		// Update renderer
		application.renderer.Render(transformsToRender, mesh);

		// Update input system
		application.inputSystem->Update();

		// Update the UI layer's frame
		//UILayer::UpdateFrame();

		// PS: You want to have all logic and that stuff before this call 
		// Clear buffers and poll
		application.window.UpdateBuffers();
	}
}

void FluidSimulationDemo::InputCheck()
{
	if (!started && application.inputSystem->GetKeyDown(GLFW_KEY_SPACE))
	{
		started = true;
		float rx = 0.3f;
		float ry = 0.6f;
		float rz = 1.0f;

		for (int i = 0; i < numParticles; ++i)
		{
			float x = xMin + rx * ((float)rand() / RAND_MAX) * (xMax - xMin);
			float y = yMin + ry * ((float)rand() / RAND_MAX) * (yMax - yMin);
			float z = zMin + rz * ((float)rand() / RAND_MAX) * (zMax - zMin);

			glm::vec3 position(x, y, z);
			glm::quat orientation = glm::angleAxis(0.f, glm::vec3(0, 1, 0));
			glm::vec3 scale(radius, radius, radius);
			glm::mat3 tensor = mtrx::GenerateSphereIT(mass, radius);
			mtrx::Rigidbody* body = new mtrx::Rigidbody(mass, false, position, orientation, scale, tensor);
			
			world.AddRigidbody(body);

			transformsToRender.insert(&body->GetTransform());
			particles.push_back(new particle(restDensity, 0, body));
		}
	}
}

void FluidSimulationDemo::UpdateParticles()
{	
	//PrintPositions();

	// Update fluid density and forces
	ApplyDensity();
	ApplyForces();

	// Update positions
	UpdatePositions((float)calculateTimeStep());
}

void FluidSimulationDemo::ApplyDensity()
{
	particle* pi;
	particle* pj;
	for (int i = 0; i < particles.size(); ++i)
	{
		pi = particles[i];
		float density = 0.f;
		for (int j = 0; j < particles.size(); ++j)
		{
			if (i == j)
				continue;

			pj = particles[j];
			glm::vec3 diff = pi->rb->GetPosition() - pj->rb->GetPosition();
			float distanceSqr = glm::dot(diff, diff);

			if (distanceSqr >= smoothingRadiusSqr) // Particle is too far away
				continue;

			// p = m * kernel
			float difference = smoothingRadiusSqr - distanceSqr;
			density += pj->rb->GetMass() * poly6Coefficient * CUBE(difference);
		}

		pi->density = std::max(density, restDensity); // To avoid negative densities
		pi->pressure = K * (pi->density - restDensity); // Calculate pressure value
	}
}

void FluidSimulationDemo::ApplyForces()
{
	particle* p;
	particle* p1;
	glm::vec3 acceleration;
	glm::vec3 vdiff;
	glm::vec3 r;
	for (int i = 0; i < particles.size(); ++i)
	{
		p = particles[i];
		acceleration = glm::vec3();
		
		for (int j = 0; j < particles.size(); ++j)
		{
			if (i == j)
				continue;
			
			p1 = particles[j];
			r = p->rb->GetPosition() - p1->rb->GetPosition();
			float distSqr = glm::length2(r);

			if (distSqr == 0 || distSqr >= smoothingRadiusSqr)
				continue;
			
			float dist = 1 / InvSqrt(distSqr);
			float inv = 1 / dist;
			r = inv * r;

			float diff = smoothingRadius - dist;
			float spikeyCoefficient = spikeyGradCoefficient * SQR(diff);
			float massRatio = p1->rb->GetMass() / p->rb->GetMass();
			float pTerm = (p->pressure + p1->pressure) / (2 * p->density * p1->density);
			acceleration -= massRatio * pTerm * spikeyCoefficient * r;

			// Viscosity
			float laplacian = viscosityLaplacianCoefficient * diff;
			vdiff = p1->rb->GetVelocity() - p->rb->GetVelocity();
			acceleration += (viscosityCoefficient * massRatio * (1.f / p1->density) * laplacian) * vdiff;
		}

		acceleration += gravity;
		//acceleration += BarrierCollisionCorrection(p); // Some collision correction due to the barriers of the simulation

		float magSqr = glm::length2(acceleration);
		if (magSqr > maximumAccelerationSqr)
			acceleration = maximumAcceleration * glm::fastNormalize(acceleration);

		p->rb->SetAcceleration(acceleration);
	}
}

void FluidSimulationDemo::UpdatePositions(float dt)
{
	for (int i = 0; i < particles.size(); ++i) 
	{
		particle* p = particles[i];

		// calculate velocity at half timestep interval for leapfrog integration
		if (p->isHalfTimeStepVelocityInitialized) 
		{
			p->velocityAtHalfTimeStep += (float)dt * p->rb->GetAcceleration();
		}
		else
		{
			p->velocityAtHalfTimeStep = p->rb->GetVelocity() + (float)(0.5 * dt) * p->rb->GetAcceleration();
			p->isHalfTimeStepVelocityInitialized = true;
		}

		p->rb->GetPosition() += (float)dt * p->velocityAtHalfTimeStep;
		p->rb->GetVelocity() = p->velocityAtHalfTimeStep + (float)(0.5 * dt) * p->rb->GetAcceleration();

		if (glm::length2(p->rb->GetVelocity()) > maximumVelocitySqr) 
		{
			p->rb->SetVelocity((float)maximumVelocity * glm::fastNormalize(p->rb->GetVelocity()));
		}

		CollisionPositionCorrection(p);
	}
	//for (int i = 0; i < particles.size(); ++i)
	//{
	//	particle* p = particles[i];
	//	glm::vec3& vel = p->rb->GetVelocity();

	//	float timeStep = calculateTimeStep();

	//	p->rb->GetVelocity() += timeStep * p->rb->GetAcceleration();
	//	//p->rb->GetVelocity() *= 0.9999f;
	//	float magSqr = glm::length2(p->rb->GetVelocity());
	//	if (magSqr > SQR(maximumVelocity))
	//		p->rb->SetVelocity(maximumVelocity * glm::fastNormalize(p->rb->GetVelocity()));

	//	p->rb->GetPosition() += timeStep * p->rb->GetVelocity();

	//	CollisionPositionCorrection(p);
	//}
}

glm::vec3 FluidSimulationDemo::BarrierCollisionCorrection(particle* part)
{
	float r = boundaryForceRadius;
	float minf = minBoundaryForce;
	float maxf = maxBoundaryForce;

	glm::vec3& p = part->rb->GetPosition();
	glm::vec3 acceleration = glm::vec3(0.0, 0.0, 0.0);
	float mass = part->rb->GetMass();

	// Are these maxes and mins fine??
	if (p.x < xMin + r)
	{
		float dist = std::max(0.0f, p.x - xMin);
		float force = lerp(maxf, minf, dist / r);
		acceleration += glm::vec3(force / mass, 0.0, 0.0);
	}
	else if (p.x > xMax - r)
	{
		float dist = std::max(0.0f, xMax - p.x);
		float force = lerp(maxf, minf, dist / r);
		acceleration += glm::vec3(-force / mass, 0.0, 0.0);
	}

	if (p.y < yMin + r)
	{
		float dist = std::max(0.0f, p.y - yMin);
		float force = lerp(maxf, minf, dist / r);
		acceleration += glm::vec3(0.0, force / mass, 0.0);
	}
	else if (p.y > yMax - r) 
	{
		float dist = std::max(0.0f, yMax - p.y);
		float force = lerp(maxf, minf, dist / r);
		acceleration += glm::vec3(0.0, -force / mass, 0.0);
	}

	if (p.z < zMin + r)
	{
		float dist = std::max(0.0f, p.z - zMin);
		float force = lerp(maxf, minf, dist / r);
		acceleration += glm::vec3(0.0, 0.0, force / mass);
	}
	else if (p.z > zMax - r) 
	{
		float dist = std::max(0.0f, zMax - p.z);
		float force = lerp(maxf, minf, dist / r);
		acceleration += glm::vec3(0.0, 0.0, -force / mass);
	}

	return acceleration;
}

void FluidSimulationDemo::CollisionPositionCorrection(particle* part)
{
	float eps = 0.001f;
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
	//else if (p.y > yMax) 
	//{
	//	part->rb->SetPosition(glm::vec3(p.x, yMax - eps, p.z));
	//	part->rb->SetVelocity(glm::vec3(vel.x, -d * vel.y, vel.z));
	//}

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

double FluidSimulationDemo::calculateTimeStep() 
{
	float maxvsq = 0.0;         // max velocity squared
	float maxcsq = 0.0;         // max speed of sound squared
	float maxasq = 0.0;         // max accelleration squared
	particle* p;

	for (int i = 0; i < particles.size(); ++i) 
	{
		p = particles[i];
		float vsq = glm::dot(p->rb->GetVelocity(), p->rb->GetVelocity());
		float asq = glm::dot(p->rb->GetAcceleration(), p->rb->GetAcceleration());
		float csq = evaluateSpeedOfSoundSquared(p);
		if (vsq > maxvsq) { maxvsq = vsq; }
		if (csq > maxcsq) { maxcsq = csq; }
		if (asq > maxasq) { maxasq = asq; }
	}

	float maxv = sqrt(maxvsq);
	float maxc = sqrt(maxcsq);
	float maxa = sqrt(maxasq);

	float vStep = courantSafetyFactor * smoothingRadius / std::min(1.0f, maxv);
	float cStep = courantSafetyFactor * smoothingRadius / maxc;
	float aStep = sqrt(smoothingRadius / maxa);
	float tempMin = std::min(vStep, cStep);

	return std::min(minTimeStep, fmin(tempMin, aStep));
}

