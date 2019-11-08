#include "PrecompiledHeader.h"
#include "FluidSimulationDemo.h"

// Particle Parameters
float radius = 0.1f;
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
float spikeyGradCoefficient = -45.f / (PI * pow(smoothingRadius, 6.f));
float viscosityLaplacianCoefficient = 45.f / (PI * pow(smoothingRadius, 6.f));
float poly6Coefficient = (315.f / (64.f * PI * pow(smoothingRadius, 9.f)));
float smoothingRadiusSqr = SQR(smoothingRadius);

// Obstacle Parameters
float stuckToBoundaryRadius = 0.01f;
float boundaryDampingCoefficient = 0.6f;
double boundaryForceRadius = 0.1f;
double minBoundaryForce = 0.0;
double maxBoundaryForce = 0.0;


float xMin = -10.f;
float yMin = -2.5f;
float zMin = -2.5f;
float xMax = 10.f;
float yMax = 6.f;
float zMax = 5.f;

float courantSafetyFactor = 1.0f;
float minTimeStep = 1.0 / 240.0;

// 
glm::vec3 gravity = glm::vec3(0, -5.f, 0);
bool started = false;

FluidSimulationDemo::FluidSimulationDemo() : Demo("Fluid Simulation Demo", 1280, 720), numParticles(500), startSim(false)
{
	mesh = 2;
	application.camera->GetTransform().SetPosition(glm::vec3(10.f, 2.f, 30.f));
	//application.camera->GetTransform().Rotate(glm::angleAxis(-180.f, glm::vec3(0, 1, 0)));
	application.window.SetVsync(true);
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
		glm::vec3 startPos(1.f, 2.f, 0);
		float offset = radius * 2.f;
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
	//PrintPositions();

	// Update fluid density and forces
	ApplyDensity();
	ApplyForces();

	// Update positions
	UpdatePositions();
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
			float distanceSqr = glm::length2(diff);

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
			float dist = glm::length(r);

			if (dist == 0 || dist >= smoothingRadius)
				continue;
			
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
			acceleration += viscosityCoefficient * massRatio * ((1.f / p1->density) * laplacian) * vdiff;
		}

		acceleration += gravity;
		//acceleration += BarrierCollisionCorrection(p); // Some collision correction due to the barriers of the simulation

		// Motion damping
		float mag = glm::length(acceleration);
		glm::vec3 damp = p->rb->GetVelocity() * motionDampingCoefficent;
		if (glm::length(damp) > mag)
			acceleration = glm::vec3();
		else
			acceleration -= damp;


		if (mag > 75.f)
			acceleration = 75.f * (acceleration / mag);

		p->rb->SetAcceleration(acceleration);
	}
}

void FluidSimulationDemo::UpdatePositions()
{
	for (int i = 0; i < particles.size(); ++i)
	{
		particle* p = particles[i];

		glm::vec3& vel = p->rb->GetVelocity();

		float timeStep = calculateTimeStep();
		p->rb->GetVelocity() += timeStep * p->rb->GetAcceleration();


		float magSqr = glm::length2(p->rb->GetVelocity());
		if (magSqr > 50.f)
			p->rb->SetVelocity(7.f * glm::fastNormalize(p->rb->GetVelocity()));

		p->rb->GetPosition() += timeStep * 0.2f * p->rb->GetVelocity();

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
	double eps = 0.0001;
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

double FluidSimulationDemo::calculateTimeStep() {
	double maxvsq = 0.0;         // max velocity squared
	double maxcsq = 0.0;         // max speed of sound squared
	double maxasq = 0.0;         // max accelleration squared
	particle* p;

	for (int i = 0; i < particles.size(); ++i) {
		p = particles[i];
		double vsq = glm::dot(p->rb->GetVelocity(), p->rb->GetVelocity());
		double asq = glm::dot(p->rb->GetAcceleration(), p->rb->GetAcceleration());
		double csq = evaluateSpeedOfSoundSquared(p);
		if (vsq > maxvsq) { maxvsq = vsq; }
		if (csq > maxcsq) { maxcsq = csq; }
		if (asq > maxasq) { maxasq = asq; }
	}

	double maxv = sqrt(maxvsq);
	double maxc = sqrt(maxcsq);
	double maxa = sqrt(maxasq);

	double vStep = courantSafetyFactor * smoothingRadius / fmax(1.0, maxv);
	double cStep = courantSafetyFactor * smoothingRadius / maxc;
	double aStep = sqrt(smoothingRadius / maxa);
	double tempMin = fmin(vStep, cStep);

	//qDebug() << maxv << maxa << maxc;

	return fmax(minTimeStep, fmin(tempMin, aStep));
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
