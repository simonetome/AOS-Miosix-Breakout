#include "game.h"
#include "../settings.h"
#include "gameObj/block.h"


Game::Game()
{

}

void Game::newGame(Canvas canvas)
{
    score=0;
    Block block[BLOCK_ROW][(ROW-2)/BLOCK_WIDTH];
    canvas.changeCanvasMode();
    canvas.printTheBoard();
    canvas.setCanvasMode();


}

Game::~Game()
{

}