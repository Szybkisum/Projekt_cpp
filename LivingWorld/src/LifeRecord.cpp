#include "LifeRecord.h"
#include <fstream>

LifeRecord::LifeRecord(int birthTurn) : birthTurn(birthTurn), deathTurn(-1) {}

int LifeRecord::getBirthTurn() const
{
    return birthTurn;
}

int LifeRecord::getDeathTurn() const
{
    return deathTurn;
}

void LifeRecord::setDeathTurn(int deathTurn)
{
    this->deathTurn = deathTurn;
}

std::string LifeRecord::toString() const
{
    return "(" + std::to_string(birthTurn) + ", " + std::to_string(deathTurn) + ")";
}

void LifeRecord::saveTo(std::ostream& out) const
{
    out.write(reinterpret_cast<const char*>(&birthTurn), sizeof(birthTurn));
    out.write(reinterpret_cast<const char*>(&deathTurn), sizeof(deathTurn));
}

void LifeRecord::loadFrom(std::istream& in)
{
    in.read(reinterpret_cast<char*>(&birthTurn), sizeof(birthTurn));
    in.read(reinterpret_cast<char*>(&deathTurn), sizeof(deathTurn));
}