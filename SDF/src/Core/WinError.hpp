/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#pragma once

#include <SDF/Core/WinTypes.hpp>

#include <string>

namespace sdf {

	struct WinError {

		DWORD code;
		std::string message;

		static WinError getLastError();
		static WinError getLastWSAError();

		static WinError fromCOM(const HRESULT hResult);

	private:
		static WinError formatMessage(const DWORD messageId);

	};

}
