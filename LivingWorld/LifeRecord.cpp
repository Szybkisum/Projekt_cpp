#include "LifeRecord.h"

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

