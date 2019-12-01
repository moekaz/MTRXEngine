#pragma once

// Experimental GLM definition
#define GLM_ENABLE_EXPERIMENTAL

// C/C++ default libraries
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <filesystem>
#include <stdio.h>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <fstream>
#include <array>

// SpdLog
#include <spdlog/spdlog.h>
#include <spdlog/logger.h>
#include <spdlog/sinks/basic_file_sink.h>

// Logger Wrapper
#include <log/LogManager.h>

// GLM
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/common.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/fast_square_root.hpp>

// Have to have imgui here since changing new will break the code
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

// TBD: ADD Premake support

// PS: THIS HAS TO BE AT THE VERY END OF THE PCH SINCE IT REDEFINES "new" WHICH MIGHT BREAK SOME LIB CODE
// Debugging tools
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define DBG_NEW new (_NORMAL_BLOCK , __FILE__ , __LINE__)
#define new DBG_NEW
#endif
