#ifndef __MAIN_GAME__
#define __MAIN_GAME__

#include <stdio.h>
#include <stdbool.h>
#include <conio.h>
#include <stdlib.h>
#include "boardfunctions.h"
#include "keys.h"
#include "filereader.h"
#include "types.h"
#include "hardcore.h"

#define N 9

int mainGame(Game current_loaded_game, bool new_game_or_not);

#endif
