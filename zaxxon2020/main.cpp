#include "pch.h"
#include "Game.h"
#include <direct.h>



int main()
{
    _mkdir("data");
    Game game;
    game.run();
    
    return EXIT_SUCCESS;
}