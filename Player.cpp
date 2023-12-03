#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2, '@');

    playerPosList = new objPosArrayList();
    playerPosList->insertHead(tempPos);
}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos()
{
    // return the reference to the playerPos arrray list
    return playerPosList;
}

void Player::updatePlayerDir()
{
    // Use GameMechs input processing to get input for direction
    char input = mainGameMechsRef->getInput();
    // PPA3 input processing logic
    switch(input)
    {
        //Esc key exit
        case 27:
            mainGameMechsRef->setLoseFlag();    //Lose condition since game was not completed
            mainGameMechsRef->setExitTrue();
            break;
        case 'w':
            if (myDir == UP || myDir == DOWN) //Not allowed
            {
                    break;
            }
            myDir = UP;
            break;

        case 'a':
            if (myDir == LEFT || myDir == RIGHT) //Not allowed
            {
                break;
            }
            myDir = LEFT;
            break;

        case 's':
            if (myDir == DOWN || myDir == UP) //Not allowed
            {
                break;
            }   
            myDir = DOWN;
            break;

        case 'd':
            if (myDir == RIGHT || myDir == LEFT) //Not allowed
            {
                break;
            }
            myDir = RIGHT;
            break;

        default:
            break;
    }        
}

void Player::movePlayer()
{
    objPos currHead;
    objPos food, body;
    playerPosList->getHeadElement(currHead);
    // PPA3 Finite State Machine logic
    switch(myDir)
    {
        case STOP:
            break;
        case UP:
            currHead.y = currHead.y-1;
            if(currHead.y == 0)
            {
                currHead.y = mainGameMechsRef->getBoardSizeY()-2;
            }
            break;
        case LEFT:
            currHead.x = currHead.x-1;
            if(currHead.x == 0)
            {
                currHead.x = mainGameMechsRef->getBoardSizeX()-2;
            }
            break;
        case DOWN:
            currHead.y = currHead.y+1;
            if(currHead.y == mainGameMechsRef->getBoardSizeY()-1)
            {
                currHead.y = 1;
            }
            break;
        case RIGHT:
            currHead.x = currHead.x+1;
            if(currHead.x == mainGameMechsRef->getBoardSizeX()-1)
            {
                currHead.x = 1;
            }
            break;
        default:
            break;
    }

    //Collisions
    playerPosList->insertHead(currHead);
    mainGameMechsRef->getFoodPos(food);
    playerPosList->getHeadElement(currHead);
    if(currHead.x == food.x && currHead.y == food.y) //Food consumption check
    {
        mainGameMechsRef->incrementScore();
        mainGameMechsRef->generateFood(playerPosList);
    }
    else
    {
        playerPosList->removeTail();
    }
    for(int i = 1; i <= playerPosList->getSize(); i++)   //Check with every element of the body apart from head.
    {
        playerPosList->getElement(body, i);
        if(currHead.x == body.x && currHead.y == body.y)//Body collision check
        {
            //Set lose and exits
            mainGameMechsRef->setLoseFlag();
            mainGameMechsRef->setExitTrue();
        }
    }
}

