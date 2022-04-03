/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#pragma once

#include <SDF/Core/WinTypes.hpp>
#include <SDF/Core/Exception.hpp>

#include <string>

#define WSA_THROW() { \
    WinError error = WinError::getLastWSAError(); \
    throw NetworkException(error.message, error.code); \
}

#define WSA_ASSERT(x) \
    if (!(x)) { \
        WSA_THROW(); \
    }

#define COM_CALL(hResult) \
    if (FAILED(hResult)) { \
        WinError error = WinError::fromCOM(hResult); \
        throw SystemException(error.message, error.code); \
    }

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
