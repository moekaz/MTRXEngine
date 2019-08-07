/*
	Author: Mohamed Kazma
	Description: Some time calculations needed for physics calculations
*/

#pragma once

#include <IUpdateable.h>

namespace mtrx
{
	class GameTime : public IUpdateable
	{
	public:
		static float deltaTime;	// The delta time between frames in seconds

		static void PhysicsUpdate();	// Update the time values
		static float GetStartTime();	// Get the start time
		static float GetCurrentTime();	// Get the current time
		static void Init();
		static float GetTime();	// Get the current time


	private:
		static const float startTime;	// The starting time of the application
		static float currentTime;	// The current time that we are in
		static float prevCurrentTime;	// The previous current time to calculate delta time

		static void CalculateDeltaTime();	// Find delta time based on start and current time for the time spent on a frame

	protected:
	};
}