#include "Sheep.h"
#include <unordered_set>

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

bool Sheep::interactsWith(std::string species) const
{
    std::unordered_set<std::string> interactions = {"G", "D", "T"};
    return (interactions.count(species)) ? true : false;
}

std::shared_ptr<Organism> Sheep::clone(const Position& pos, int birthTurn) const
{
    return std::make_shared<Sheep>(pos, birthTurn, getAncestorHistory());
}