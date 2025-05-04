#include "Organism.h"
#include <iostream>

Organism::Organism()
	: power(0),
	initiative(0),
	liveLength(6),
	powerToReproduce(3),
	position(0, 0),
	lifeRecord(std::make_shared<LifeRecord>(0)),
	ancestorHistory{lifeRecord},
	species("O") {}

Organism::Organism(int power, int initiative, int liveLength, int powerToReproduce, Position position, int birthTurn)
	: power(power),
	initiative(initiative),
	liveLength(liveLength),
	powerToReproduce(powerToReproduce),
	position(position),
	lifeRecord(std::make_shared<LifeRecord>(birthTurn)),
	ancestorHistory{lifeRecord},
	species("O") {}

Organism::Organism(int power, int initiative, int liveLength, int powerToReproduce, Position position, int birthTurn, std::vector<std::shared_ptr<LifeRecord>> ancestorHistory)
	: power(power),
	initiative(initiative),
	liveLength(liveLength),
	powerToReproduce(powerToReproduce),
	position(position),
	lifeRecord(std::make_shared<LifeRecord>(birthTurn)),
	ancestorHistory(std::move(ancestorHistory)),
	species("O")
	{
		this->ancestorHistory.push_back(lifeRecord);
	}

int Organism::getPower() const
{
	return power;
}

void Organism::setPower(int power)
{
	this->power = power;
}

int Organism::getInitiative() const
{
	return initiative;
}

int Organism::getLiveLength() const
{
	return liveLength;
}

void Organism::setLiveLength(int liveLength)
{
	this->liveLength = liveLength;
}

int Organism::getPowerToReproduce() const
{
	return powerToReproduce;
}

Position Organism::getPosition() const
{
	return position;
}

void Organism::setPosition(Position position)
{
	this->position = position;
}

std::string Organism::getSpecies() const
{
	return species;
}

void Organism::setSpecies(std::string species)
{
	this->species = species;
}

const std::vector<std::shared_ptr<LifeRecord>>& Organism::getAncestorHistory() const {
    return ancestorHistory;
}

bool Organism::canReproduce() const
{
	return power >= powerToReproduce;
}

bool Organism::isDead() const
{
	return liveLength <= 0;
}

std::string Organism::toString() const
{
	std::string result = "{ species: " + species +
		   ", power: " + std::to_string(power) +
		   ", initiative: " + std::to_string(initiative) +
		   ", liveLength: " + std::to_string(liveLength) +
		   ", powerToReproduce: " + std::to_string(powerToReproduce) +
		   ", position: " + position.toString() + 
		   ", lifeRecord: " + lifeRecord->toString() + 
		   ", ancestorHistiry: ";
	for (auto& rec : ancestorHistory) {
		result += rec -> toString() + " ";
	}
	return result + "}";
}

void Organism::recordDeath(int deathTurn)
{
    lifeRecord->setDeathTurn(deathTurn);
}

void Organism::saveTo(std::ostream& out,
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
}

void Organism::loadFrom(std::istream& in, const std::vector<std::shared_ptr<LifeRecord>>& idToRecord) {
    int temp;
    in.read(reinterpret_cast<char*>(&power), sizeof(power));
    in.read(reinterpret_cast<char*>(&initiative), sizeof(initiative));
    in.read(reinterpret_cast<char*>(&liveLength), sizeof(liveLength));
    in.read(reinterpret_cast<char*>(&powerToReproduce), sizeof(powerToReproduce));
    int posX, posY;
    in.read(reinterpret_cast<char*>(&posX), sizeof(posX));
    in.read(reinterpret_cast<char*>(&posY), sizeof(posY));
    position = Position(posX, posY);
    int hist_size;
    in.read(reinterpret_cast<char*>(&hist_size), sizeof(hist_size));
    ancestorHistory.clear();
    for (int i = 0; i < hist_size; ++i) {
        int id;
        in.read(reinterpret_cast<char*>(&id), sizeof(id));
        ancestorHistory.push_back(idToRecord[id]);
    }
    lifeRecord = ancestorHistory.back();
}