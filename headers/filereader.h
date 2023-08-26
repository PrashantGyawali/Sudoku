#ifndef __FILEREADER__
#define __FILEREADER__

#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "keys.h"
#include "types.h"
#include "types2.h"
#include "boardfunctions.h"
#include "sleep.h"

int getDateInteger();

void emptyboardinit(Board a);

void empty_Game_Init(Game *gm,GlGameSettings settings);

Game* read_games(int* numgames);

void write_game(Game gamedata,char update_or_del);

void SavedGamesMenu(Game *Self, int* has_loaded_the_game);

#endif