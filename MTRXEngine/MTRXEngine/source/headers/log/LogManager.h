/*
	Author: Mohamed Kazma
	Description: A logger class that allows us to log information to a log file
	Uses the library spdlog with a wrapper to be used within our API 
*/

#pragma once

#define LOG_FILE_DIR "MTRXLogs\\" // Directory where log file will be created in

// Macros for API calls to log information
#define MTRX_WARN(...) mtrx::LogManager::GetInstance().warn(__VA_ARGS__)
#define MTRX_INFO(...) mtrx::LogManager::GetInstance().info(__VA_ARGS__)
#define MTRX_TRACE(...) mtrx::LogManager::GetInstance().trace(__VA_ARGS__)
#define MTRX_ERROR(...) mtrx::LogManager::GetInstance().error(__VA_ARGS__)
#define MTRX_CRITICAL(...) mtrx::LogManager::GetInstance().critical(__VA_ARGS__)

namespace mtrx
{
	class LogManager
	{
	public:
		static LogManager& GetInstance()
		{
			static LogManager logManager;
			return logManager;
		}

		/* API for the logger to abstract library used and make it simple if we change libraries */
		template<typename T>
		inline void warn(const T& msg) { mtrxLogger->warn(msg); }
		template<typename T>
		inline void info(const T& msg) { mtrxLogger->info(msg); }
		template<typename T>
		inline void trace(const T& msg) { mtrxLogger->trace(msg); }
		template<typename T>
		inline void error(const T& msg) { mtrxLogger->error(msg); }
		template<typename T>
		inline void critical(const T& msg) { mtrxLogger->critical(msg); }

	private:
		std::shared_ptr<spdlog::logger> mtrxLogger; // Store a pointer to the logger that the engine will be using		
		void CreateLogDirectory(); // Sets up the log directory to be used by the logger to log information onto

		LogManager();

		// We do not want to the logger to be modifiable
		LogManager(const LogManager&) = delete; 
		void operator=(const LogManager&) = delete;
	};
}