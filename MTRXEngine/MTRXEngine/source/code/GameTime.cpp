/*
	Author: Mohamed Kazma
	Description: Some calculations of the game's time
*/

#include <PrecompiledHeader.h>
#include <GameTime.h>

namespace mtrx
{
	// Setup the main values needed 
	const float GameTime::startTime = (float)time(0);
	float GameTime::currentTime = startTime;
	float GameTime::prevCurrentTime = NULL;
	float GameTime::deltaTime = 0;

	// Update 
	void GameTime::PhysicsUpdate()
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
		return (float)time(0);
	}

	// Calculate delta time
	void GameTime::CalculateDeltaTime()
	{
		deltaTime = currentTime - prevCurrentTime;
	}
}