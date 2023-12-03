#include "objPosArrayList.h"

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_MAX_CAP];
    listSize = 0;
    arrayCapacity = ARRAY_MAX_CAP;
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

int objPosArrayList::getSize()
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    listSize++;
    if (listSize < arrayCapacity){ // only inserts when listSize is less than arrayCapacity
        for (int i =listSize -1; i>0; i--){
            aList[i].setObjPos(aList[i-1]); // this will shuffle all elements towards tail
        }
        aList[0].setObjPos(thisPos); 
    }
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if (listSize < arrayCapacity){ // only inserts when listSize is less than arrayCapacity
        aList[listSize].setObjPos(thisPos); 
        listSize++; 
    }
}

void objPosArrayList::removeHead()
{
    if (listSize >0){
        for (int i =0; i < listSize -1; i++){
            aList[i]= aList[i+1];
        }
        listSize--; 
    }
}

void objPosArrayList::removeTail()
{
    if (listSize >0){
        listSize--; 
     }
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[0]);
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[listSize-1]);
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    if (index>= 0 && index < listSize){
    returnPos.setObjPos(aList[index]); 
    }
}