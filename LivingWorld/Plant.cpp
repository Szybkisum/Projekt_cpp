#include "Plant.h"

Plant::Plant(int power, int initiative, int liveLength, int powerToReproduce, Position position, int birthTurn)
    : Organism(power, initiative, liveLength, powerToReproduce, position, birthTurn)
{
	setSpecies("P");
}

Plant::Plant(int power, int initiative, int liveLength, int powerToReproduce, Position position, int birthTurn, std::vector<std::shared_ptr<LifeRecord>> ancestorHistory)
    : Organism(power, initiative, liveLength, powerToReproduce, position, birthTurn, ancestorHistory)
{
	setSpecies("P");
}

std::shared_ptr<Organism> Plant::clone(const Position& pos, int birthTurn) const
{
    return std::make_shared<Plant>(0, 5, 5, 2, pos, birthTurn, getAncestorHistory());
}

void Plant::move(int dx, int dy)
{
	move(0, 0);
}