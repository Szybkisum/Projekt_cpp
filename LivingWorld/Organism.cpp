#include "Organism.h"
#include <iostream>

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

void Organism::move(int dx, int dy)
{
	position.move(dx, dy);
}