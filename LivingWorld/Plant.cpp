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

bool Plant::interactsWith(std::string species) const
{
	return false;
}

void Plant::move(Position pos)
{
	return;
}