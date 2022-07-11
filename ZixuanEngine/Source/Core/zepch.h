#pragma once

#include "Core.h"
#include "Utils/Typedefs.h"
#include "Utils/Colors/Color.h"
#include "Utils/Log/Logger.h"

#include <assert.h>
#include <algorithm>
#include <memory>
#include <utility>
#include <functional>
#include <sstream>
#include <iostream>
#include <string>

#include <vector>
#include <unordered_map>

#ifdef ZE_PLATFORM_WINDOWS
	#include <Windows.h>
#endif