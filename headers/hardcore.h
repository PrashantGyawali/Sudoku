#ifdef _WIN32
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <shellapi.h>
#include "sleep.h"

#define deletegmae() cs_win()

void alert();
void cs_win();

#else 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define deletegmae() cs_uni()

void cs_uni();

#endif
