#include <SDF/Core/Time.hpp>

#include <windows.h>

#include <iostream>

namespace sdf {

    Timer::Timer() {
        reset();
    }

    void Timer::reset() {

        LARGE_INTEGER largeInt;
        QueryPerformanceFrequency(&largeInt);

        frequency = largeInt.QuadPart;
        QueryPerformanceCounter(&largeInt);
        startTime = largeInt.QuadPart;

    }

    LONGLONG Timer::getElapsedTime() {

        LARGE_INTEGER largeInt;
        QueryPerformanceCounter(&largeInt);

        LONGLONG elapsedTime = largeInt.QuadPart - startTime;
        elapsedTime *= 1000000;
        elapsedTime /= frequency;

        return elapsedTime;

    }

    double Timer::getElapsedMilliseconds() {
        return (double)getElapsedTime() / 1000.0;
    }
    double Timer::getElapsedMicroseconds() {
        return (double)getElapsedTime();
    }

}
