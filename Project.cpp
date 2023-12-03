#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "objPosArrayList.h"


using namespace std;

#define DELAY_CONST 100000

GameMechs* myGM;
Player* player;

char input;
int rows;
int cols;
int score;
bool loseStatus;
char dispString[21];

objPos *itemBin;

enum State{
    STATIONARY,
    UP,
    LEFT,
    DOWN,
    RIGHT
};
enum State currState;

bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();
    
    myGM = new GameMechs(26, 13);
    player = new Player(myGM);

    objPosArrayList* tempPos = player->getPlayerPos();
    myGM->generateFood(tempPos);


}

void GetInput(void)
{
    myGM->getInput();
}

void RunLogic(void)
{
    player->updatePlayerDir();
    player->movePlayer();

    myGM->clearInput();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();    
    int x,y, i;

    bool drawn;

    objPosArrayList *playerBody = player->getPlayerPos();
    objPos tempBody;

    objPos tempFoodPos;
    myGM->getFoodPos(tempFoodPos);
    for (y = 0; y < myGM->getBoardSizeY(); y++)
    {
        for(x = 0; x < myGM->getBoardSizeX(); x++)
        {
            drawn = false;
            for(i = 0; i < playerBody->getSize(); i++)
            {
                playerBody->getElement(tempBody, i);
                if(tempBody.x == x && tempBody.y == y)
                {
                    dispString[x] = tempBody.symbol;
                    drawn = true;
                    break;
                }
            }
            if(drawn) continue;
            if(y == 0 || y == myGM->getBoardSizeY() - 1 || x == 0 || x == myGM->getBoardSizeX()-1)
            {
                dispString[x] = '#';
            }
            else if(tempFoodPos.x == x && tempFoodPos.y == y)
            {
                dispString[x] = tempFoodPos.symbol;
            }
            else
            {
                dispString[x] = ' ';
            }
        }
        MacUILib_printf("%s", dispString);
        MacUILib_printf("%c", '\n');
    }
    MacUILib_printf("Score <%d>\n", myGM->getScore());
    MacUILib_printf("Food <%d,%d>", tempFoodPos.x, tempFoodPos.y);
    score = myGM->getScore(); //store for game over screen
    loseStatus = myGM->getLoseFlag();
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();
    //Use to check game winning condition since it will be deleted in myGM
    int x = myGM->getBoardSizeX();
    int y = myGM->getBoardSizeY();    
    delete myGM;
    delete player;
    if(loseStatus == true) //Lose condition
    {
        MacUILib_printf("You lose. You scored: %d", score);
    }
    else if(((x-2)*(y-2)-1)==score)    //Win condition
    {
        MacUILib_printf("You beat the game!");
    }
    MacUILib_uninit();
    
}
