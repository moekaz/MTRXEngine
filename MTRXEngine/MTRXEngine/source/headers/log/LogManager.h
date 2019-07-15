/*
	Author: Mohamed Kazma
	Description: A logger class that allows us to log information to a log file
	Uses the library spdlog with a wrapper to be used within our API 
*/

#pragma once

#define LOG_FILE_DIR "MTRXLogs\\" // Directory where log file will be created in

// Macros for API calls to log information
#define MTRX_WARN(...) mtrx::LogManager::warn(__VA_ARGS__)
#define MTRX_INFO(...) mtrx::LogManager::info(__VA_ARGS__)
#define MTRX_TRACE(...) mtrx::LogManager::trace(__VA_ARGS__)
#define MTRX_ERROR(...) mtrx::LogManager::error(__VA_ARGS__)
#define MTRX_CRITICAL(...) mtrx::LogManager::critical(__VA_ARGS__)

namespace mtrx
{
	class LogManager
	{
	public:
		static void Init(); // Initialize the logger

		/* API for the logger to abstract library used and make it simple if we change libraries */
		template<typename T>
		inline static void warn(const T& msg) { mtrxLogger->warn(msg); }
		template<typename T>
		inline static void info(const T& msg) { mtrxLogger->info(msg); }
		template<typename T>
		inline static void trace(const T& msg) { mtrxLogger->trace(msg); }
		template<typename T>
		inline static void error(const T& msg) { mtrxLogger->error(msg); }
		template<typename T>
		inline static void critical(const T& msg) { mtrxLogger->critical(msg); }

	private:
		static std::shared_ptr<spdlog::logger> mtrxLogger; // Store a pointer to the logger that the engine will be using		
		static void CreateLogDirectory(); // Sets up the log directory to be used by the logger to log information onto

	protected:
	};
}