#include <SDF/Core/Clock.hpp>

#include <windows.h>

namespace sdf {

    Clock::Clock() {
        restart();
    }

    void Clock::restart() {
        startTime = getTime();
    }

    LONGLONG Clock::getFrequency() {
        LARGE_INTEGER largeInt;
        QueryPerformanceFrequency(&largeInt);
        return largeInt.QuadPart;
    }

    LONGLONG Clock::getTime() {

        static LONGLONG frequency = getFrequency();

        LARGE_INTEGER largeInt;
        QueryPerformanceCounter(&largeInt);

        LONGLONG time = largeInt.QuadPart;
        time *= 1000000;
        time /= frequency;

        return time;

    }

    ClockUnit Clock::getElapsed() const {
        return ClockUnit((double)(getTime() - startTime));
    }

}
