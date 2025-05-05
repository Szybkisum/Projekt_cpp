#include "World.h"
#include "Grass.h"
#include "Sheep.h"
#include "Dandelion.h"
#include "Wolf.h"
#include "Toadstool.h"
#include "rendering.h"
#include <random>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <iostream>

static std::mt19937& rng() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return gen;
}

World::World() : World(6, 6) {};
World::World(int worldX, int worldY) : worldX(worldX), worldY(worldY) {};

std::shared_ptr<Organism> World::getOrganismFromPosition(int x, int y) const 
{
	auto it = std::find_if(
        organisms.begin(), organisms.end(),
        [&](const std::shared_ptr<Organism>& org) {
            return org->getPosition().getX() == x && org->getPosition().getY() == y;
        }
    );
	return (it != organisms.end()) ? *it : nullptr;
}

std::string World::getSpeciesFromPosition(int x, int y) const
{	
	std::shared_ptr<Organism> org = getOrganismFromPosition(x, y);
	return (org) ? org->getSpecies() : "";
}

bool World::isPositionOnWorld(int x, int y) const
{
	return (x >= 0 && y >= 0 && x < worldX && y < worldY);
}

bool World::isPositionFree(Position position) const
{
	return getSpeciesFromPosition(position.getX(), position.getY()).empty();
}

int World::getWorldX() const
{
	return worldX;
}

void World::setWorldX(int worldX)
{
	this->worldX = worldX;
}

int World::getWorldY() const
{
	return worldY;
}

void World::setWorldY(int worldY)
{
	this->worldY = worldY;
}

int World::getTurn() const
{
	return turn;
}

std::vector<Position> World::getVectorOfFreePositionsAround(Position position) const
{	
	int pos_x = position.getX(), pos_y = position.getY();
	std::vector<Position> result;
	for (int x = -1; x <= 1; ++x)
		for (int y = -1; y <= 1; ++y) {
			if (x == 0 && y == 0) continue;
			int new_x = pos_x + x, new_y = pos_y + y;

			if (isPositionOnWorld(new_x, new_y) && isPositionFree(Position(new_x, new_y)))
				result.emplace_back(new_x, new_y);
		}
	return result;
}

std::vector<Position> World::getVectorOfPossiblePositionsForOrganism(std::shared_ptr<Organism> org) const
{
	Position position = org->getPosition();
	int pos_x = position.getX(), pos_y = position.getY();
	std::vector<Position> result;
	for (int x = -1; x <= 1; ++x)
		for (int y = -1; y <= 1; ++y) {
			if (x == 0 && y == 0) continue;
			int new_x = pos_x + x, new_y = pos_y + y;
			if (isPositionOnWorld(new_x, new_y) &&
			(isPositionFree(Position(new_x, new_y)) || org -> interactsWith(getSpeciesFromPosition(new_x, new_y))))
				result.emplace_back(new_x, new_y);
		}
	return result;
}

void World::removeOrganism(std::shared_ptr<Organism> org)
{
	organisms.erase(
		std::find_if(
			organisms.begin(), organisms.end(),
			[&](const std::shared_ptr<Organism>& ptr){ return ptr.get() == org.get(); }
	));
}

void World::addOrganismPtr(std::shared_ptr<Organism> org) 
{
	auto it = std::find_if(
		organisms.begin(), organisms.end(),
		[&](const std::shared_ptr<Organism>& existing) {
			return existing->getInitiative() < org->getInitiative();
		}
	);
	organisms.insert(it, org);
};

void World::makeTurn()
{
	std::vector<std::shared_ptr<Organism>> current = organisms;
	for (std::shared_ptr<Organism> org : current) {
		if (org->isDead()) continue;
		std::vector<Position> possiblePositions = getVectorOfPossiblePositionsForOrganism(org);
		std::vector<Position> freePositions = getVectorOfFreePositionsAround(org->getPosition());
		bool reproduced = false;

		if (!freePositions.empty() && org->canReproduce()) {
			std::uniform_int_distribution<size_t> dist(0, freePositions.size() - 1);
			Position pos = freePositions[dist(rng())];
			std::shared_ptr<Organism> child = org->clone(pos, turn);
            addOrganismPtr(child);
			org->setPower(org->getPower() / 2);
			reproduced = true;
		} else if (!possiblePositions.empty()) {
			std::uniform_int_distribution<size_t> dist(0, possiblePositions.size() - 1);
			Position pos = possiblePositions[dist(rng())];
			auto other = getOrganismFromPosition(pos.getX(), pos.getY());
			if (other) {
				org->collision(other);
				if (other->isDead()) {
					other->recordDeath(turn);
					removeOrganism(other);
				}
			} else {
				org -> move(pos);
			}
		}
		if (!reproduced) org->setPower(org->getPower() + 1);
		org->setLiveLength(org->getLiveLength() - 1);
		if (org->isDead()){
			org->recordDeath(turn);
            removeOrganism(org);
		}
	}
	turn++;
}

void World::saveTo(std::string fileName) const
{
	std::ofstream out(fileName, std::ios::binary);
	if (!out) return;
	out.write(reinterpret_cast<const char*>(&worldX), sizeof(worldX));
	out.write(reinterpret_cast<const char*>(&worldY), sizeof(worldY));
	out.write(reinterpret_cast<const char*>(&turn),   sizeof(turn));

	std::unordered_map<LifeRecord*, int> recordToID;
	std::vector<std::shared_ptr<LifeRecord>> idToRecord;
	int nextID = 0;

	for (const std::shared_ptr<Organism>& org : organisms) {
  		for (const std::shared_ptr<LifeRecord>& recPtr : org->getAncestorHistory()) {
    		auto raw = recPtr.get();
    		if (!recordToID.count(raw)) {
      			recordToID[raw] = nextID++;
      			idToRecord.push_back(recPtr);
    		}
  		}
	}

	int recCount = idToRecord.size();
	out.write(reinterpret_cast<const char*>(&recCount), sizeof(recCount));
	for (auto& rec : idToRecord) {
  		rec->saveTo(out);  
	}

	int count = organisms.size();
	out.write(reinterpret_cast<const char*>(&count), sizeof(count));
	for (auto& org : organisms) {
		org->saveTo(out, recordToID);
	}
}

void World::loadFrom(const std::string& fileName) {
    std::ifstream in(fileName, std::ios::binary);
    if (!in) return;
    organisms.clear();
    in.read(reinterpret_cast<char*>(&worldX), sizeof(worldX));
    in.read(reinterpret_cast<char*>(&worldY), sizeof(worldY));
    in.read(reinterpret_cast<char*>(&turn), sizeof(turn));

    int recordCount;
    in.read(reinterpret_cast<char*>(&recordCount), sizeof(recordCount));
    std::vector<std::shared_ptr<LifeRecord>> idToRecord(recordCount);

    for (int i = 0; i < recordCount; ++i) {
        auto rec = std::make_shared<LifeRecord>();
        rec->loadFrom(in);
        idToRecord[i] = rec;
    }

    int organismCount;
    in.read(reinterpret_cast<char*>(&organismCount), sizeof(organismCount));
    for (int i = 0; i < organismCount; ++i) {
		int ssz;
    	in.read(reinterpret_cast<char*>(&ssz), sizeof(ssz));
    	std::string species(ssz, '\0');
    	in.read(&species[0], ssz);
		std::shared_ptr<Organism> org;
		if (species == "G") org = std::make_shared<Grass>();
		else if (species == "S") org = std::make_shared<Sheep>();
		else if (species == "D") org = std::make_shared<Dandelion>();
		else if (species == "W") org = std::make_shared<Wolf>();
		else if (species == "T") org = std::make_shared<Toadstool>();
        org->loadFrom(in, idToRecord);
        addOrganismPtr(org);
    }
}

std::string World::toString() const
{
	std::string result = "\nturn: " + std::to_string(getTurn()) + "\n";
	std::string spec;

	for (int wY = 0; wY < getWorldY(); ++wY) {
		for (int wX = 0; wX < getWorldX(); ++wX) {
			spec = getSpeciesFromPosition(wX, wY);
			if (spec != "")
				result += spec;
			else
				result += separator;
		};
		result += "\n";
	}
	return result;
}

void World::printOrganisms() const
{
	for (auto& uptr : organisms) {
		std::cout << uptr->toString() << std::endl;
	}
}