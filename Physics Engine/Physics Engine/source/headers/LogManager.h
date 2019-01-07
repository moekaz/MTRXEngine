/*
	Author: Mohamed Kazma
	Description: A logger class that allows us to log information to a log file
	Uses the library spdlog with a wrapper to be used within our API 
*/

#pragma once

#define LOG_FILE_DIR "MTRXLogs\\"

// Macros for API calls to log information
#define MTRX_WARN(...) MTRX::LogManager::GetMTRXLogger()->warn(__VA_ARGS__)
#define MTRX_INFO(...) MTRX::LogManager::GetMTRXLogger()->info(__VA_ARGS__)
#define MTRX_TRACE(...) MTRX::LogManager::GetMTRXLogger()->trace(__VA_ARGS__)
#define MTRX_ERROR(...) MTRX::LogManager::GetMTRXLogger()->error(__VA_ARGS__)
#define MTRX_CRITICAL(...) MTRX::LogManager::GetMTRXLogger()->critical(__VA_ARGS__)

namespace MTRX
{
	class LogManager
	{
	public:
		static void init(); // Initialize the logger
		inline static std::shared_ptr<spdlog::logger>& GetMTRXLogger() { return mtrxLogger; } // Getter for the logger 

	private:
		static std::shared_ptr<spdlog::logger> mtrxLogger; // Store a pointer to the logger that the engine will be using		
		static void CreateLogDirectory();
	protected:

	};
}