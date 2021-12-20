#include "Fruit.h"
#include <iostream>;

// Data structurs final HW TCSD-14 2021
// Yiftach Navot 304956279
// Raanan Tivoni 302500228

Fruit::Fruit(int id, int ripe_rate) : m_id(id), m_ripeRate(ripe_rate)
{
}


const int Fruit::getId() const
{
    return m_id;
}

const int Fruit::getRipeRate() const
{
    return m_ripeRate;
}

void Fruit::updateRipeRate(int ripeRate)
{
    m_ripeRate = ripeRate;
}

bool Fruit::operator>(Fruit& other) const
{
    if (this->m_ripeRate == other.m_ripeRate)
    {
        if (this->m_id == other.m_id)
        {
            throw "two fruits with same ID";
        }
        return this->m_id > other.m_id;
    }

    return this->m_ripeRate > other.m_ripeRate;
}

bool Fruit::operator<(Fruit& other) const
{
    return !(*this > other);
}

