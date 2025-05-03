#include "Wolf.h"

Wolf::Wolf(Position position, int birthTurn)
    : Animal(8, 5, 20, 16, position, birthTurn)
{
    setSpecies("W");
}

Wolf::Wolf(Position position, int birthTurn, std::vector<std::shared_ptr<LifeRecord>> ancestorHistory)
    : Animal(8, 5, 20, 16, position, birthTurn, ancestorHistory)
{
    setSpecies("W");
}

std::shared_ptr<Organism> Wolf::clone(const Position& pos, int birthTurn) const
{
    return std::make_shared<Wolf>(pos, birthTurn, getAncestorHistory());
}