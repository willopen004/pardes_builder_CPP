#include "library1.h"
#include "Pardes.h"

// Data structurs final HW TCSD-14 2021
// Yiftach Navot 304956279
// Raanan Tivoni 302500228

void* Init(int N)
{
    if (N <= 0)
    {
        return NULL;
    }

    Pardes *DS = new Pardes(N);
    if (!DS)
    {
        return NULL;
    }
    return (void*)DS;
}

StatusType PlantTree(void *DS, int i, int j)
{
    if (!DS)
    {
        return INVALID_INPUT;
    }
    return ((Pardes*)DS)->PlantTreeInternal(i,j);
}

StatusType AddFruit(void* DS, int i, int j, int fruitID, int ripeRate)
{
    if (!DS)
    {
        return INVALID_INPUT;
    }
    return ((Pardes*)DS)->AddFruitInternal(i,j,fruitID,ripeRate);
}

StatusType PickFruit(void* DS, int fruitID)
{
    if (!DS)
    {
        return INVALID_INPUT;
    }
    return ((Pardes*)DS)->PickFruitInternal(fruitID);
}

StatusType RateFruit(void* DS, int fruitID, int ripeRate)
{
    if (!DS)
    {
        return INVALID_INPUT;
    }
    return ((Pardes*)DS)->RateFruitInternal(fruitID, ripeRate);
}

StatusType GetBestFruit(void* DS, int i, int j, int* fruitID)
{
    if (!DS || !fruitID)
    {
        return INVALID_INPUT;
    }
    return ((Pardes*)DS)->GetBestFruitInternal(i, j, fruitID);
}

StatusType GetAllFruitsByRate(void* DS, int i, int j, int** fruits, int* numOfFruits)
{
    if (!DS || !fruits || !numOfFruits)
    {
        return INVALID_INPUT;
    }
    return ((Pardes*)DS)->GetAllFruitsByRateInternal(i, j, fruits, numOfFruits);
}

StatusType UpdateRottenFruits(void* DS, int rottenBase, int rottenFactor)
{
    if (!DS)
    {
        return INVALID_INPUT;
    }
    return ((Pardes*)DS)->UpdateRottenFruitsInternal(rottenBase, rottenFactor);
}

void Quit(void** DS)
{
    ((Pardes*)*DS)->InternalQuit(DS);
    *DS = nullptr;
}

