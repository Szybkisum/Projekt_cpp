#include "Animal.h"

Animal::Animal(int power, int initiative, int liveLength, int powerToReproduce, Position position, int birthTurn)
    : Organism(power, initiative, liveLength, powerToReproduce, position, birthTurn)
{
    lastPosition = position;
	setSpecies("A");
}

Animal::Animal(int power, int initiative, int liveLength, int powerToReproduce, Position position, int birthTurn, std::vector<std::shared_ptr<LifeRecord>> ancestorHistory)
    : Organism(power, initiative, liveLength, powerToReproduce, position, birthTurn, ancestorHistory)
{
    lastPosition = position;
	setSpecies("A");
}

void Animal::collision(std::shared_ptr<Organism> other)
{
    if (getPower() > other -> getPower()) {
        other -> setLiveLength(0);
        if (other -> getSpecies() == "T") {
            setLiveLength(0);
        }
    }
}

void Animal::move(Position position)
{
    lastPosition = getPosition();
	setPosition(position);
}