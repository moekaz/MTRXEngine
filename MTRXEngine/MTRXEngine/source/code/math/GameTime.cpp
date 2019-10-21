/*
	Author: Mohamed Kazma
	Description: Some calculations of the game's time
*/

#include <PrecompiledHeader.h>
#include <math/GameTime.h>

namespace mtrx
{
	// Setup the main values needed 
	const float GameTime::startTime = GetTime();
	float GameTime::currentTime = startTime;
	float GameTime::prevCurrentTime = 0.f;
	float GameTime::deltaTime = 0.f;

	void GameTime::Init()
	{
		currentTime = GetTime();
		prevCurrentTime = 0.f;
		deltaTime = 0.f;
	}

	// Update 
	void GameTime::Update()
	{
		// Set the previous to the current
		prevCurrentTime = currentTime;
		// Get the current time
		currentTime = GameTime::GetTime();
		// Calculate delta time
		CalculateDeltaTime();
	}

	// Get the current time
	float GameTime::GetCurrentTime()
	{
		return currentTime;
	}

	// Get the start time of the application (mostly for logging and stuff like that)
	float GameTime::GetStartTime()
	{
		return startTime;
	}

	// Gets what time it is right now
	float GameTime::GetTime()
	{
		return (float)glfwGetTime();
	}

	// Calculate delta time
	void GameTime::CalculateDeltaTime()
	{
		deltaTime = currentTime - prevCurrentTime;
	}
}