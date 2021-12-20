#ifndef TREE_H
#define TREE_H
#include <utility>
#include <list>
#include "Fruit.h"

// Data structurs final HW TCSD-14 2021
// Yiftach Navot 304956279
// Raanan Tivoni 302500228

using std::make_pair;
using std::list;

class Tree
{
public:
	Tree(int i, int j);
	~Tree();
	void AddFruitsToTree(Fruit* fruit);
	void DeleteFruitsFromTree(int fruitID);
	void updateRottenFruits(int rottenBase, int rottenFactor);
	int* GetAllFruitsIdOnTreeByRate();
	int GetBestFruit() const;
	const Coor& GetTreeCoor() const;
	int GetNumOfFruits() const;
	bool IsFruitListEmpty() const;

private:
	void insertFruitSorted(Fruit* fruit);

	list<Fruit*> m_fruitRipeIdSortedList;
	Coor m_coordinates;
};

#endif // TREE_H