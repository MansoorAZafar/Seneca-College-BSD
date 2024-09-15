#include "Timer.h"

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | September 24, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

void sdds::Timer::start()
{
	this->begin = std::chrono::steady_clock::now(); // stores the time starting point
}

long long sdds::Timer::stop()
{
	const auto end = std::chrono::steady_clock::now(); // stores the time ending point
	const auto nanos = std::chrono::duration_cast<std::chrono::nanoseconds>(end - this->begin);
	return nanos.count();

}
