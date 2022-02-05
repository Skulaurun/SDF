#pragma once

#include "WinTypes.hpp"

namespace sdf {

    struct ClockUnit {

        ClockUnit(const double time)
            : time(time) {}

        double asSeconds() const { return time; }
        double asMilliseconds() const { return time * 1000; }
        double asMicroseconds() const { return time * 100000; }

        operator double() { return asMicroseconds(); }

    private:
        double time;

    };

    class Clock {
        static_assert(sizeof(LONGLONG) == sizeof(double));

    public:
        Clock();

        void restart();
        ClockUnit getElapsed() const;

        static ClockUnit getNow() { return ClockUnit(getTime()); }

    private:
        static double getTime();
        static double getFrequency();

    private:
        double startTime;

    };

}
