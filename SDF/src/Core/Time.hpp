#pragma once

#include "WinTypes.hpp"

namespace sdf {

	class Timer {

	public:
		Timer();

		void reset();
		double getElapsedMilliseconds();
		double getElapsedMicroseconds();

	private:
		LONGLONG getElapsedTime();

	private:
		LONGLONG frequency;
		LONGLONG startTime;

	};

}
