#pragma once

#include "WinTypes.hpp"

namespace sdf {

    struct ClockUnit {

        ClockUnit(const double time)
            : time(time) {}

        double asSeconds() const { return time / 100000; }
        double asMilliseconds() const { return time / 1000; }
        double asMicroseconds() const { return time; }

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

        static ClockUnit getNow() { return ClockUnit((double)getTime()); }

    private:
        static LONGLONG getTime();
        static LONGLONG getFrequency();

    private:
        LONGLONG startTime;

    };

}
