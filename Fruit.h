#ifndef FRUIT_H
#define FRUIT_H
#include <utility>

// Data structurs final HW TCSD-14 2021
// Yiftach Navot 304956279
// Raanan Tivoni 302500228

using std::pair;
typedef pair<int, int> Coor;

class Fruit
{
public:
	Fruit(int id, int ripe_rate = 0);
	~Fruit() = default;
	const int getId() const;
	const int getRipeRate() const;
	void updateRipeRate(int ripeRate);
	bool operator>(Fruit& other) const;
	bool operator<(Fruit& other) const;

private:
	const int m_id;
	int m_ripeRate;

};

#endif // FRUIT_H