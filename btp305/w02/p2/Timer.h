#ifndef SDDS_TIMER_H
#define SDDS_TIMER_H
#include <iostream>
#include <chrono>

// Mansoor Ahmad Zafar | mzafar15@myseneca.ca | 100503226 | September 24, 2023
//
// I have done all the coding myself and only copied the code
// that my professor provided to complete my workshops and assignments.

namespace sdds{
	class Timer
	{
		std::chrono::time_point<std::chrono::steady_clock> begin{};

	public:
		void start();
		long long stop();
	};
}
#endif
