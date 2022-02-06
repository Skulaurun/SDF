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

}
