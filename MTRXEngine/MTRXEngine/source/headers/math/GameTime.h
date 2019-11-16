#pragma once

namespace mtrx
{
	class GameTime
	{
	public:
		static float deltaTime;	// The delta time in seconds
		
		/**
		 * @return The time difference between 2 timepoints in seconds
		 * its a double for more precision
		 */
		static inline double FindTimeDiffSeconds(const std::chrono::high_resolution_clock::time_point& t1, const std::chrono::high_resolution_clock::time_point& t2)
		{
			return std::chrono::duration<double>(t1 - t2).count();
		}

		/**
		 * Initialization code
		 */
		static inline void Init() { currentTime = GetTime(); }
		
		/**
		 * Update time values for calculating delta time
		 */
		static inline void Update()
		{
			prevCurrentTime = currentTime;
			currentTime = GetTime();
			CalculateDeltaTime();
		}
		
		/**
		 * @return time elapsed since the start of the application
		 */
		static inline float GetTimeSeconds() { return (float)FindTimeDiffSeconds(GetTime(), startTime); }

		/**
		 * @return Wrapper for getting the current time
		 */
		static inline std::chrono::high_resolution_clock::time_point GetTime() { return std::chrono::high_resolution_clock::now(); }
		
	private:
		static const std::chrono::high_resolution_clock::time_point startTime;
		static std::chrono::high_resolution_clock::time_point currentTime;
		static std::chrono::high_resolution_clock::time_point prevCurrentTime;

		/**
		 * Calculate delta time
		 */
		static inline void CalculateDeltaTime()
		{
			deltaTime = (float)FindTimeDiffSeconds(currentTime, prevCurrentTime);
		}
	};
}