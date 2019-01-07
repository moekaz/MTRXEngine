/*
	Author: Mohamed Kazma
	Description: Precompiled header for the MTRX project
*/

#pragma once

#define GLM_ENABLE_EXPERIMENTAL

// C/C++ default libraries
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <filesystem>
#include <time.h>
#include <stdio.h>

// MTRX defs
#include <Defs.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

// SpdLog
#include <spdlog/spdlog.h>
#include <spdlog/logger.h>
#include <spdlog/sinks/basic_file_sink.h>

// Premake