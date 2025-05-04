#include "Grass.h"

Grass::Grass() : Plant()
{
    species = "G";
}

Grass::Grass(Position position, int birthTurn)
    : Plant(0, 0, 6, 3, position, birthTurn)
{
    species = "G";
}

Grass::Grass(Position position, int birthTurn, std::vector<std::shared_ptr<LifeRecord>> ancestorHistory)
    : Plant(0, 0, 6, 3, position, birthTurn, ancestorHistory)
{
    species = "G";
}

std::shared_ptr<Organism> Grass::clone(const Position& pos, int birthTurn) const
{
    return std::make_shared<Grass>(pos, birthTurn, getAncestorHistory());
}