#include "Grass.h"

Grass::Grass(Position position, int birthTurn)
    : Plant(0, 0, 6, 3, position, birthTurn)
{
    setSpecies("G");
}

Grass::Grass(Position position, int birthTurn, std::vector<std::shared_ptr<LifeRecord>> ancestorHistory)
    : Plant(0, 0, 6, 3, position, birthTurn, ancestorHistory)
{
    setSpecies("G");
}

std::shared_ptr<Organism> Grass::clone(const Position& pos, int birthTurn) const
{
    return std::make_shared<Grass>(pos, birthTurn, getAncestorHistory());
}