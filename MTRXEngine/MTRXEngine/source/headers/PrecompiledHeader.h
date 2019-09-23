/*
	Author: Mohamed Kazma
	Description: Precompiled header for the mtrx project
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
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <fstream>

// SpdLog
#include <spdlog/spdlog.h>
#include <spdlog/logger.h>
#include <spdlog/sinks/basic_file_sink.h>

// GLM
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/common.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/fast_square_root.hpp>

// GLAD
#include <glad/glad.h>

// GLFW
#include <GLFW/glfw3.h>

// Imgui
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

// Premake
