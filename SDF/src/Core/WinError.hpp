#pragma once

#include <SDF/Core/WinTypes.hpp>

#include <string>

namespace sdf {

	struct WinError {

		DWORD code;
		std::string message;

		static WinError getLastError();

	};

}
