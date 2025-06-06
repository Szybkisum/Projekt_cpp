#include "Toadstool.h"

Toadstool::Toadstool() : Plant()
{
    species = "T";
}

Toadstool::Toadstool(Position position, int birthTurn)
    : Plant(0, 0, 12, 4, position, birthTurn)
{
    species = "T";
}

Toadstool::Toadstool(Position position, int birthTurn, std::vector<std::shared_ptr<LifeRecord>> ancestorHistory)
    : Plant(0, 0, 12, 4, position, birthTurn, ancestorHistory)
{
    species = "T";
}

std::shared_ptr<Organism> Toadstool::clone(const Position& pos, int birthTurn) const
{
    return std::make_shared<Toadstool>(pos, birthTurn, getAncestorHistory());
}