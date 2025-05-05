#include "Wolf.h"
#include <unordered_set>

Wolf::Wolf() : Animal()
{
    species = "W";
}

Wolf::Wolf(Position position, int birthTurn)
    : Animal(8, 5, 20, 16, position, birthTurn)
{
    species = "W";
}

Wolf::Wolf(Position position, int birthTurn, std::vector<std::shared_ptr<LifeRecord>> ancestorHistory)
    : Animal(8, 5, 20, 16, position, birthTurn, ancestorHistory)
{
    species = "W";
}

bool Wolf::interactsWith(std::string species) const
{
    std::unordered_set<std::string> interactions = {"S", "T"};
    return (interactions.count(species)) ? true : false;
}

std::shared_ptr<Organism> Wolf::clone(const Position& pos, int birthTurn) const
{
    return std::make_shared<Wolf>(pos, birthTurn, getAncestorHistory());
}