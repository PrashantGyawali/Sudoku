typedef int Board[9][9];

#ifndef __GAME_DEFINED__ // Check if Game struct is not defined
#define __GAME_DEFINED__ // Define it to prevent redefinition

typedef struct Gamesdata {
    int lastmodified;
    int id;
    struct Settings {
        int ai;
        int hint;
        int gamemode;
        int slow;
    } settings;

    Board initialgrid;
    Board grid;
    Board errorgrid;
} Game;

#endif // __GAME_DEFINED__