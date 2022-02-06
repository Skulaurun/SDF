#include <PCH.hpp>

#include "WinError.hpp"

#include <system_error>

namespace sdf {

    WinError WinError::getLastError() {

        DWORD error = GetLastError();
        if (error == 0) {
            return { error, "" };
        }

        // TODO: Fix language, guarantee English

        LPSTR buffer = {};
        DWORD size = FormatMessageA(
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_ALLOCATE_BUFFER |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            error,
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

        return { error, std::string(ptr.get(), size) };

    }

}
