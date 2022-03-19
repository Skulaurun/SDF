/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#include <PCH.hpp>

#include "WinError.hpp"

#include <system_error>

#pragma comment (lib, "Ws2_32.lib")

namespace sdf {

    WinError WinError::getLastError() {
        return formatMessage(GetLastError());
    }

    WinError WinError::getLastWSAError() {
        return formatMessage(WSAGetLastError());
    }

    WinError WinError::fromCOM(const HRESULT hResult) {
        return formatMessage(HRESULT_CODE(hResult));
    }

    WinError WinError::formatMessage(const DWORD messageId) {

        if (messageId == 0) {
            return { messageId, "" };
        }
        
        // TODO: Fix language, guarantee English

        LPSTR buffer = {};
        DWORD size = FormatMessageA(
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_ALLOCATE_BUFFER |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            messageId,
            0,
            (LPSTR)&buffer,
            0,
            NULL
        );

        if (size == 0) {
            throw std::system_error(
                GetLastError(),
                std::system_category(),
                "Failed to retrieve error message string from system."
            );
        }

        std::unique_ptr<char, void(*)(char*)> ptr(buffer, [](char* p) {
            LocalFree(p);
        });

        return { messageId, std::string(ptr.get(), size) };

    }

}
