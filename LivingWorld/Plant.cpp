#include "Plant.h"
#include <ostream>
#include <istream>

Plant::Plant() : Organism()
{
	species = "P";
}

Plant::Plant(int power, int initiative, int liveLength, int powerToReproduce, Position position, int birthTurn)
    : Organism(power, initiative, liveLength, powerToReproduce, position, birthTurn)
{
	species = "P";
}

Plant::Plant(int power, int initiative, int liveLength, int powerToReproduce, Position position, int birthTurn, std::vector<std::shared_ptr<LifeRecord>> ancestorHistory)
    : Organism(power, initiative, liveLength, powerToReproduce, position, birthTurn, ancestorHistory)
{
	species = "P";
}

bool Plant::interactsWith(std::string species) const
{
	return false;
}

void Plant::collision(std::shared_ptr<Organism> other) 
{
	return;
}

void Plant::move(Position pos)
{
	return;
}