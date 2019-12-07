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
	/**
	 * @brief Logger wrapper for logging functionality in the engine
	 * 
	 */
	class LogManager
	{
	public:
		/**
		 * @brief Get the singleton logger instance
		 * 
		 * @return LogManager& The instance of the logger that we will be using
		 */
		static inline LogManager& GetInstance()
		{
			static LogManager logManager;
			return logManager;
		}

		/**
		 * @brief Wrapper for logging a warning
		 * 
		 * @tparam T Type of warning that we will be logging
		 * @param msg The message that we log
		 */
		template<typename T>
		inline void warn(const T& msg) { mtrxLogger->warn(msg); }
		
		/**
		 * @brief Wrapper for logging an info level message
		 * 
		 * @tparam T Type of warning that we will be logging
		 * @param msg The message that we log
		 */
		template<typename T>
		inline void info(const T& msg) { mtrxLogger->info(msg); }
		
		/**
		 * @brief Wrapper for logging a trace level message
		 * 
		 * @tparam T Type of warning that we will be logging
		 * @param msg The message that we log
		 */
		template<typename T>
		inline void trace(const T& msg) { mtrxLogger->trace(msg); }
		
		/**
		 * @brief Wrapper for logging an error level message
		 * 
		 * @tparam T Type of warning that we will be logging
		 * @param msg The message that we log
		 */
		template<typename T>
		inline void error(const T& msg) { mtrxLogger->error(msg); }
		
		/**
		 * @brief Wrapper for logging a critical level message
		 * 
		 * @tparam T Type of warning that we will be logging
		 * @param msg The message that we log
		 */
		template<typename T>
		inline void critical(const T& msg) { mtrxLogger->critical(msg); }

	private:
		std::shared_ptr<spdlog::logger> mtrxLogger; // Store a pointer to the logger that the engine will be using	

		/**
		 * @brief Create The log directory that we will use for logging if it does not exist
		 * 
		 */
		void CreateLogDirectory();

		/**
		 * @brief Construct a new Log Manager object.
		 * This object is a singleton so it will be constructed once
		 * 
		 */
		LogManager();

		// We do not want the logger to be modifiable
		LogManager(const LogManager&) = delete;
		LogManager(const LogManager&&) = delete;

		LogManager& operator=(const LogManager&) = delete;
		LogManager& operator=(const LogManager&&) = delete;
	};
}