#include "GameMechs.h"
#include "MacUILib.h"

GameMechs::GameMechs()
{
    input = 0;
    score = 0;
    exitFlag = false;
    loseFlag = false;
    boardSizeX = 30;
    boardSizeY = 15;

    foodPos.setObjPos(-1, -1, 'o');
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    score = 0;
    exitFlag = false;
    loseFlag = false;
    boardSizeX = boardX;
    boardSizeY = boardY;

    foodPos.setObjPos(-1, -1, 'o');
}

// do you need a destructor?
//No new heaps created so no need


bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

char GameMechs::getInput()
{
    if(MacUILib_hasChar())
    {
        input = MacUILib_getChar();
    }

    return input;
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

bool GameMechs::getLoseFlag()
{
    return loseFlag;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}

int GameMechs::getScore()
{
    return score;
}

void GameMechs::incrementScore()
{
    score++;
}

void GameMechs::generateFood(objPosArrayList* blockOff)
{
    objPos element;
    //Generate one item first.
    srand(time(0));
    foodPos.setObjPos((rand() % (boardSizeX-2)) + 1, (rand() % (boardSizeY-2)) + 1,'o');
    for(int i = 0; i <= blockOff->getSize(); i++)//check with entire list.
    {
        blockOff->getElement(element, i);
        while(foodPos.isPosEqual(&element))//Loop until food isn't on the snake body
        {
            srand(time(0));
            foodPos.setObjPos((rand() % (boardSizeX-2)) + 1, (rand() % (boardSizeY-2)) + 1,'o');
            i = 0; //Check from the start of snake body again
        }
    }
}

void GameMechs::getFoodPos(objPos &returnPos)
{
    returnPos = foodPos;
}