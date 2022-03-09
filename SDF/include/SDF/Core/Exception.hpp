/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#pragma once

#include <string>
#include <exception>

namespace sdf {

    class Exception : public std::exception {

    public:
        explicit Exception(const std::string& message) noexcept
            : std::exception(message.c_str()) {}

    };

    class SystemException : public Exception {

    public:
        explicit SystemException(const std::string& message, const uint64_t code) noexcept
            : Exception(message), code(code) {}

        virtual uint64_t error() { return code; }

    private:
        uint64_t code;

    };

}
