#include "Animal.h"

Animal::Animal(int power, int initiative, int liveLength, int powerToReproduce, Position position, int birthTurn)
    : Organism(power, initiative, liveLength, powerToReproduce, position, birthTurn)
{
	setSpecies("A");
}

Animal::Animal(int power, int initiative, int liveLength, int powerToReproduce, Position position, int birthTurn, std::vector<std::shared_ptr<LifeRecord>> ancestorHistory)
    : Organism(power, initiative, liveLength, powerToReproduce, position, birthTurn, ancestorHistory)
{
	setSpecies("A");
}

std::shared_ptr<Organism> Animal::clone(const Position& pos, int birthTurn) const
{
    return std::make_shared<Animal>(0, 5, 5, 2, pos, birthTurn, getAncestorHistory());
}

void Animal::move(Position position)
{
	setPosition(position);
}