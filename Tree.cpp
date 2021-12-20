#include "Tree.h"
#include <iostream>
#include <cassert>

// Data structurs final HW TCSD-14 2021
// Yiftach Navot 304956279
// Raanan Tivoni 302500228

Tree::Tree(int i, int j) : m_fruitRipeIdSortedList()
{
    m_coordinates = make_pair(i, j);
}

Tree::~Tree()
{
    while (!m_fruitRipeIdSortedList.empty())
    {
        
        delete *(m_fruitRipeIdSortedList.begin());
        m_fruitRipeIdSortedList.erase(m_fruitRipeIdSortedList.begin());
    }
}

void Tree::AddFruitsToTree(Fruit* fruit)
{
    insertFruitSorted(fruit);
}

void Tree::DeleteFruitsFromTree(int fruitID)
{
    auto it = m_fruitRipeIdSortedList.begin();
    
    while ((*it)->getId() != fruitID) // while the id dont match
    {
        if (it == m_fruitRipeIdSortedList.end())
        {
            throw "no fruit with this ID in this Tree";
        }
        it++; // keep going
    }
    Fruit* fruit_ptr = *it;
    m_fruitRipeIdSortedList.erase(it); // erase the pointer from thr list
    delete fruit_ptr; // erase the object
}

int Tree::GetBestFruit() const
{
    if (m_fruitRipeIdSortedList.empty())
    {
        return -1;
    }
    return (*m_fruitRipeIdSortedList.begin())->getId();
}

const Coor& Tree::GetTreeCoor() const
{
    return m_coordinates;
}

int Tree::GetNumOfFruits() const
{
    return m_fruitRipeIdSortedList.size();
}

bool Tree::IsFruitListEmpty() const
{
    return m_fruitRipeIdSortedList.empty();
}

int* Tree::GetAllFruitsIdOnTreeByRate()
{
    int* arrayOfFruitsIdOnTree = (int*)malloc(sizeof(int) * GetNumOfFruits());
    int i = 0;
    for (auto it = m_fruitRipeIdSortedList.begin(); it != m_fruitRipeIdSortedList.end(); it++)
    {
        std::cout << i+1 << "    ||    " << (*it)->getId() << "    ||    " << (*it)->getRipeRate() << std::endl;
        arrayOfFruitsIdOnTree[i++] = (*it)->getId();
    }
    return arrayOfFruitsIdOnTree;
}

void Tree::updateRottenFruits(int rottenBase, int rottenFactor)
{
    int size_of_list = m_fruitRipeIdSortedList.size();
    list<Fruit*> rotten_fruits;
    list<Fruit*> ok_fruits;
    
    for (auto it = m_fruitRipeIdSortedList.begin(); it != m_fruitRipeIdSortedList.end(); ++it)
    {
        if ((*it)->getId() % rottenBase == 0)
        {
            (*it)->updateRipeRate((*it)->getRipeRate() * rottenFactor);
            rotten_fruits.push_back(*it);
        }
        else
        {
            ok_fruits.push_back(*it);
        }
    }
    m_fruitRipeIdSortedList.clear();
    assert(m_fruitRipeIdSortedList.empty());

    list<Fruit*>::iterator rotten_it = rotten_fruits.begin();
    list<Fruit*>::iterator ok_it = ok_fruits.begin();

    while (rotten_it != rotten_fruits.end() && ok_it != ok_fruits.end())
    {
        
        if ((*rotten_it)->getRipeRate() < (*ok_it)->getRipeRate())
        {
            m_fruitRipeIdSortedList.push_back((*rotten_it));
            rotten_it++;
        }
        else if ((*rotten_it)->getRipeRate() == (*ok_it)->getRipeRate())
        {
            if ((*rotten_it)->getId() < (*ok_it)->getId())
            {
                m_fruitRipeIdSortedList.push_back((*rotten_it));
                rotten_it++;
            }
            else
            {
                m_fruitRipeIdSortedList.push_back((*ok_it));
                ok_it++;
            }
        }
        else
        {
            m_fruitRipeIdSortedList.push_back((*ok_it));
            ok_it++;
        }
    }
    if (ok_it != ok_fruits.end())
    {
        assert(rotten_it == rotten_fruits.end());
        while (ok_it != ok_fruits.end())
        {
            m_fruitRipeIdSortedList.push_back((*ok_it));
            ok_it++;
        }
    }
    else
    {
        while (rotten_it != rotten_fruits.end())
        {
            m_fruitRipeIdSortedList.push_back((*rotten_it));
            rotten_it++;
        }
    }
    assert(m_fruitRipeIdSortedList.size() == size_of_list);
}

void Tree::insertFruitSorted(Fruit* fruit)
{
    auto it = m_fruitRipeIdSortedList.begin();
    while(it != m_fruitRipeIdSortedList.end() && **it < *fruit)
    {
        it++;
    }
    m_fruitRipeIdSortedList.insert(it, fruit);
}
