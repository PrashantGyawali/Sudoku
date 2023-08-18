#ifndef CROSS_SLEEP_H
#define CROSS_SLEEP_H

#ifdef _WIN32
#include <windows.h>
#define cross_sleep(ms) Sleep(ms)
#else
#include <unistd.h>
#define cross_sleep(ms) usleep((ms) * 1000)
#endif
#endif // CROSS_SLEEP_H
