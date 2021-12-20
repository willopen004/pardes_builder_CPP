#include "Pardes.h"
#include <iostream>

// Data structurs final HW TCSD-14 2021
// Yiftach Navot 304956279
// Raanan Tivoni 302500228

Pardes::Pardes(int N) : m_fieldSize(N), m_rowsMap()
{
    std::cout << "Init done." << std::endl;
}

Pardes::~Pardes()
{
}

StatusType Pardes::PlantTreeInternal(int i, int j)
{
    Coor coordinates = make_pair(i, j);
    if (i < 0 || i >= m_fieldSize || j < 0 || j >= m_fieldSize)
    {
        return INVALID_INPUT;
    }
    if (m_rowsMap[i][j] != nullptr) // if the already exist
    {
        return FAILURE;
    }
    Tree* tree_to_plant = new Tree(i, j); // create a new tree
    if (!tree_to_plant) // if creation failed
    {
        return ALLOCATION_ERROR;
    }

    if (m_rowsMap[i].empty()) // if row i is empty
    {
        map<int, Tree*> new_row_map; // make a new j col
        new_row_map[j] = tree_to_plant; // insert the tree to j col
        m_rowsMap[i] = new_row_map; // insert the j col in the i row
    } 
    else 
    {
        m_rowsMap[i][j] = tree_to_plant;
    }

    return SUCCESS;
}

StatusType Pardes::AddFruitInternal(int i, int j, int fruitID, int ripeRate)
{
    Coor coordinates = make_pair(i, j);
    if (i < 0 || i >= m_fieldSize || j < 0 || j >= m_fieldSize || ripeRate <= 0 || fruitID <= 0)
    {
        return INVALID_INPUT;
    }

    if (m_rowsMap[i][j] == nullptr ||  m_fruitIdToCoor.contains(fruitID)) // if the tree or the fruit does not exist
    {
        return FAILURE;
    }
    m_fruitIdToCoor[fruitID] = coordinates; // insert coordinates to the fruit list
    Fruit* fruit_to_add = new Fruit(fruitID, ripeRate); // create new fruit
    if (!fruit_to_add) // if creation failed
    {
        return ALLOCATION_ERROR;
    }
    m_rowsMap[i][j]->AddFruitsToTree(fruit_to_add);

    return SUCCESS;
}

StatusType Pardes::PickFruitInternal(int fruitID)
{
    if (fruitID <= 0)
    {
        return INVALID_INPUT;
    }
    else if (!m_fruitIdToCoor.contains(fruitID)) // if the fruit does not exist
    {
        return FAILURE;
    }
    Coor coordinates = m_fruitIdToCoor[fruitID];
    m_rowsMap[coordinates.first][coordinates.second]->DeleteFruitsFromTree(fruitID);
    m_fruitIdToCoor.erase(fruitID);

    return SUCCESS;
}

StatusType Pardes::RateFruitInternal(int fruitID, int ripeRate)
{
    if (fruitID <= 0 || ripeRate <= 0)
    {
        return INVALID_INPUT;
    }
    else if (!m_fruitIdToCoor.contains(fruitID)) // if the fruit does not exist
    {
        return FAILURE;
    }
    Coor coordinates = m_fruitIdToCoor[fruitID];
    PickFruitInternal(fruitID);
    AddFruitInternal(coordinates.first, coordinates.second, fruitID, ripeRate);

    return SUCCESS;	
}

StatusType Pardes::GetBestFruitInternal(int i, int j, int* fruitID) 
{
    if (i < 0 || i >= m_fieldSize || j < 0 || j >= m_fieldSize || !fruitID)
    {
        return INVALID_INPUT;
    }
    Coor coordinates = make_pair(i, j);
    *fruitID = m_rowsMap[i][j]->GetBestFruit();
    std::cout << "Best fruit is: " << *fruitID << std::endl;
    return SUCCESS;
}

StatusType Pardes::GetAllFruitsByRateInternal(int i, int j, int** fruits, int* numOfFruits)
{
    if (i < 0 || i >= m_fieldSize || j < 0 || j >= m_fieldSize)
    {
        return INVALID_INPUT;
    }
    Coor coordinates = make_pair(i, j);
    if (m_rowsMap[i][j] == nullptr) // if the tree does not exist
    {
        return FAILURE;
    }
    if (m_rowsMap[i][j]->IsFruitListEmpty())
    {
        *fruits = nullptr;
        *numOfFruits = 0;
        std::cout << "and that's all!" << std::endl;
        return SUCCESS;
    }
    std::cout << "Rank ||    Fruit  || ripness" << std::endl;
    *fruits = m_rowsMap[i][j]->GetAllFruitsIdOnTreeByRate();
    *numOfFruits = m_rowsMap[i][j]->GetNumOfFruits();
    std::cout << "and that's all!" << std::endl;
    return SUCCESS;
}

StatusType Pardes::UpdateRottenFruitsInternal(int rottenBase, int rottenFactor)
{
    if (rottenBase < 1 || rottenFactor < 1)
    {
        return INVALID_INPUT;
    }

    for (auto row_map : m_rowsMap) // for every i
    {
        
        for (auto col_map : row_map.second) // for every tree in j
        {            
            col_map.second->updateRottenFruits(rottenBase, rottenFactor);
        }
    }
    return SUCCESS;
}

void Pardes::InternalQuit(void** DS)
{  
    for (auto row_map : m_rowsMap) // for every i
    {
        for (auto col_map : row_map.second) // for every tree in j
        {
            delete col_map.second;
        }
    }
    std::cout << "program quit!" << std::endl;
}

