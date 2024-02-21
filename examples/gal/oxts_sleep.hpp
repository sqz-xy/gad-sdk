#ifndef OXTS_SLEEP_HPP
#define OXTS_SLEEP_HPP

#ifdef _WIN32
#include <windows.h>
#elif __linux__
#include <unistd.h>
#endif

// This is a basic cross-platform sleep function
namespace OxTS
{
	void sleep_millisecods(int sleepMs)
	{
#ifdef __linux__
		usleep(sleepMs * 1000);   // usleep takes sleep time in us (1 millionth of a second)
#endif
#ifdef _WIN32
		Sleep(sleepMs);    // Sleep takes sleep time in ms.
#endif
	}
} // OxTS
#endif //OXTS_SLEEP_HPP