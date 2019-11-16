/*
	Author: Mohamed Kazma
	Description: Logger abstraction API to be used by the mtrx Engine
*/

#include <PrecompiledHeader.h>

#include <log/LogManager.h>

namespace mtrx
{
	LogManager::LogManager()
	{
		CreateLogDirectory(); // Setup the log directory that we need
		std::vector<spdlog::sink_ptr> loggerSinks // Create logger sinks
		{
			std::make_shared<spdlog::sinks::basic_file_sink_mt>(std::string(LOG_FILE_DIR) + "log"), // File logger sink
			std::make_shared<spdlog::sinks::wincolor_stdout_sink_mt>() // Console logger sink
		};
		mtrxLogger = std::make_shared<spdlog::logger>("MTRXLog", begin(loggerSinks), end(loggerSinks)); // Create the logger with multiple sinks	
		mtrxLogger->set_level(spdlog::level::trace); // Set logger level
		mtrxLogger->set_pattern("%^[%n] [%l] [%d-%m-%Y %T]: %v %$"); // Set the logger pattern

		spdlog::register_logger(mtrxLogger); // Register the logger that we are using
	}

	// Create/Update the directory that we want to create our log file in 
	void LogManager::CreateLogDirectory()
	{
		std::string directory = std::filesystem::current_path().string(); // Get the current directory that the project is in 
		directory += "\\" + std::string(LOG_FILE_DIR); // Add the directory that we want to create the log files in 
		if (!std::filesystem::is_directory(directory))
		{
			std::filesystem::create_directory(directory); // Create the log directory
		}
	}
}