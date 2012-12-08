/*
Checkers Game
Player vs Player
Player vs AI
AI vs AI
 */

//#include <vld.h> 
#include "lib/Game.h"

#ifdef CONSOLE
int main()
#else
int WINAPI WinMain( HINSTANCE hinstance,
                              HINSTANCE hprevinstance,
                              LPSTR lpcmdline,
                              int ncmdshow)
#endif
{
    //    Game game("board.txt");
    Game game(GameMode::AI_VS_AI, 8, Color::WHITE, AILevel::HARD);
    game.start();
    return 0;
}