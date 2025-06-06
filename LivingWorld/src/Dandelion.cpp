#include "Dandelion.h"

Dandelion::Dandelion() : Plant()
{
    species = "D";
}

Dandelion::Dandelion(Position position, int birthTurn)
    : Plant(0, 0, 6, 2, position, birthTurn)
{
    species = "D";
}

Dandelion::Dandelion(Position position, int birthTurn, std::vector<std::shared_ptr<LifeRecord>> ancestorHistory)
    : Plant(0, 0, 6, 2, position, birthTurn, ancestorHistory)
{
    species = "D";
}

std::shared_ptr<Organism> Dandelion::clone(const Position& pos, int birthTurn) const
{
    return std::make_shared<Dandelion>(pos, birthTurn, getAncestorHistory());
}