#include "Animal.h"
#include <ostream>
#include <istream>

Animal::Animal() : Organism()
{
    lastPosition = position;
	species = "A";
}

Animal::Animal(int power, int initiative, int liveLength, int powerToReproduce, Position position, int birthTurn)
    : Organism(power, initiative, liveLength, powerToReproduce, position, birthTurn)
{
    lastPosition = position;
	species = "A";
}

Animal::Animal(int power, int initiative, int liveLength, int powerToReproduce, Position position, int birthTurn, std::vector<std::shared_ptr<LifeRecord>> ancestorHistory)
    : Organism(power, initiative, liveLength, powerToReproduce, position, birthTurn, ancestorHistory)
{
    lastPosition = position;
	species = "A";
}

void Animal::collision(std::shared_ptr<Organism> other)
{
    if (power > other->getPower()) {
        other -> setLiveLength(0);
        if (other -> getSpecies() == "T") {
            liveLength = 0;
        }
    }
}

void Animal::move(Position position)
{
    lastPosition = this->position;
    this->position = position;
}

void Animal::saveTo(std::ostream& out,
    const std::unordered_map<LifeRecord*,int>& recordToID) const
{
    Organism::saveTo(out, recordToID);
    int lastPosX = lastPosition.getX(), lastPosY = lastPosition.getY();
    out.write(reinterpret_cast<const char*>(&lastPosX), sizeof(lastPosX));
    out.write(reinterpret_cast<const char*>(&lastPosY), sizeof(lastPosY));
}

void Animal::loadFrom(std::istream& in, const std::vector<std::shared_ptr<LifeRecord>>& idToRecord) {
    Organism::loadFrom(in, idToRecord);
    int lastPosX, lastPosY;
    in.read(reinterpret_cast<char*>(&lastPosX), sizeof(lastPosX));
    in.read(reinterpret_cast<char*>(&lastPosY), sizeof(lastPosY));
    lastPosition = Position(lastPosX, lastPosY);
}