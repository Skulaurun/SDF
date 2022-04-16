/*
* Copyright (c) 2021 Adam Charvát <https://www.skulaurun.eu>
* Licensed under the MIT License,
* for details see accompanying LICENSE file or a copy at
* <https://github.com/Skulaurun/SDF/blob/v1.0.0/LICENSE>.
* SPDX-License-Identifier: MIT
*/

#include <PCH.hpp>

#include <SDF/Core/Clock.hpp>

namespace sdf {

    Clock::Clock() {
        restart();
    }

    void Clock::restart() {
        startTime = getTime();
    }

    double Clock::getFrequency() {
        LARGE_INTEGER largeInt;
        QueryPerformanceFrequency(&largeInt);
        return (double)largeInt.QuadPart;
    }

    double Clock::getTime() {

        static double frequency = getFrequency();

        LARGE_INTEGER largeInt;
        QueryPerformanceCounter(&largeInt);

        return largeInt.QuadPart / frequency;

    }

    ClockUnit Clock::getElapsed() const {
        return ClockUnit(getTime() - startTime);
    }

    ClockUnit Clock::collectElapsed() {
        ClockUnit time = getElapsed();
        restart();
        return time;
    }

}
