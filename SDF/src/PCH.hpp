/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#pragma once

/* C++ STL */

#include <cstdint>
#include <string>
#include <vector>
#include <array>
#include <stack>
#include <tuple>
#include <unordered_map>

#include <cmath>
#include <memory>
#include <functional>
#include <filesystem>

#include <sstream>
#include <fstream>

/* SDF Core */

#include <SDF/Core/WinTypes.hpp>

/* System API */

#define UNICODE
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <windowsx.h>

#include <winsock2.h>
#include <ws2tcpip.h>

#include <wincodec.h>

#undef far
#undef near
