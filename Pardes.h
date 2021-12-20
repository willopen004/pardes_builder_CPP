#ifndef PARDES_H
#define PARDES_H

#include <unordered_map>
#include <map>
#include <utility>
#include "Tree.h"
#include "Fruit.h"
#include "library1.h"

// Data structurs final HW TCSD-14 2021
// Yiftach Navot 304956279
// Raanan Tivoni 302500228

using std::unordered_map;
using std::map;
using std::list;
using std::pair;
using std::make_pair;


class Pardes
{
public:
    Pardes(int N);
    ~Pardes();
    StatusType PlantTreeInternal(int i, int j);
    StatusType AddFruitInternal(int i, int j, int fruit_id, int ripe_rate);
    StatusType PickFruitInternal(int fruit_id);
    StatusType RateFruitInternal(int fruit_id, int ripe_rate);
    StatusType GetBestFruitInternal(int i, int j, int* fruit_id);
    StatusType GetAllFruitsByRateInternal(int i, int j, int** fruits, int* num_of_fruits);
    StatusType UpdateRottenFruitsInternal(int rotten_base, int rotten_factor);
    void InternalQuit(void** DS);

private:
    map<int, map<int, Tree*>> m_rowsMap; // tree of i that contains tree of j and trees
    unordered_map<int, Coor> m_fruitIdToCoor; // gets ID of fruits and return coor of tree
    int m_fieldSize;

};

#endif // PARDES_H