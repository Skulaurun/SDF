#include <SDF/Core/Clock.hpp>

#include <windows.h>

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
        return largeInt.QuadPart;
    }

    double Clock::getTime() {

        static double frequency = getFrequency();

        LARGE_INTEGER largeInt;
        QueryPerformanceCounter(&largeInt);

        return largeInt.QuadPart / (double)frequency;

    }

    ClockUnit Clock::getElapsed() const {
        return ClockUnit(getTime() - startTime);
    }

}
