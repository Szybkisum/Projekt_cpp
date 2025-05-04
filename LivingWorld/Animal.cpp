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
    int ssz = species.size();
    out.write(reinterpret_cast<const char*>(&ssz), sizeof(ssz));
    out.write(species.c_str(), ssz);

    out.write(reinterpret_cast<const char*>(&power), sizeof(power));
    out.write(reinterpret_cast<const char*>(&initiative), sizeof(initiative));
    out.write(reinterpret_cast<const char*>(&liveLength), sizeof(liveLength));
    out.write(reinterpret_cast<const char*>(&powerToReproduce), sizeof(powerToReproduce));

    int x = position.getX(), y = position.getY();
    out.write(reinterpret_cast<const char*>(&x), sizeof(x));
    out.write(reinterpret_cast<const char*>(&y), sizeof(y));
	
    int hsz = ancestorHistory.size();
    out.write(reinterpret_cast<const char*>(&hsz), sizeof(hsz));
    for (auto& rec : ancestorHistory) {
        int id = recordToID.at(rec.get());
        out.write(reinterpret_cast<const char*>(&id), sizeof(id));
    }
    int lastPosX = lastPosition.getX(), lastPosY = lastPosition.getY();
    out.write(reinterpret_cast<const char*>(&lastPosX), sizeof(lastPosX));
    out.write(reinterpret_cast<const char*>(&lastPosY), sizeof(lastPosY));
}

void Animal::loadFrom(std::istream& in, const std::vector<std::shared_ptr<LifeRecord>> idToRecord) {
    int temp;
    in.read(reinterpret_cast<char*>(&power), sizeof(power));
    in.read(reinterpret_cast<char*>(&initiative), sizeof(initiative));
    in.read(reinterpret_cast<char*>(&liveLength), sizeof(liveLength));
    in.read(reinterpret_cast<char*>(&powerToReproduce), sizeof(powerToReproduce));
    int posX, posY;
    in.read(reinterpret_cast<char*>(&posX), sizeof(posX));
    in.read(reinterpret_cast<char*>(&posY), sizeof(posY));
    position = Position(posX, posY);
    // int s_size;
    // in.read(reinterpret_cast<char*>(&s_size), sizeof(s_size));
    // species.resize(s_size);
    // in.read(&species[0], s_size);
    int hist_size;
    in.read(reinterpret_cast<char*>(&hist_size), sizeof(hist_size));
    ancestorHistory.clear();
    for (int i = 0; i < hist_size; ++i) {
        int id;
        in.read(reinterpret_cast<char*>(&id), sizeof(id));
        ancestorHistory.push_back(idToRecord[id]);
    }
    lifeRecord = ancestorHistory.back();
    int lastPosX, lastPosY;
    in.read(reinterpret_cast<char*>(&lastPosX), sizeof(lastPosX));
    in.read(reinterpret_cast<char*>(&lastPosY), sizeof(lastPosY));
    lastPosition = Position(lastPosX, lastPosY);
}