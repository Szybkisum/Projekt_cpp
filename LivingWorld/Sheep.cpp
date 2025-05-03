#include "Sheep.h"

Sheep::Sheep(Position position, int birthTurn)
    : Animal(3, 3, 10, 6, position, birthTurn)
{
    setSpecies("S");
}

Sheep::Sheep(Position position, int birthTurn, std::vector<std::shared_ptr<LifeRecord>> ancestorHistory)
    : Animal(3, 3, 10, 6, position, birthTurn, ancestorHistory)
{
    setSpecies("S");
}

std::shared_ptr<Organism> Sheep::clone(const Position& pos, int birthTurn) const
{
    return std::make_shared<Sheep>(pos, birthTurn, getAncestorHistory());
}