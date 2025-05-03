#include <random>
#include "World.h"
#include <unordered_set>

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
					organisms.erase(
						std::find_if(
							organisms.begin(), organisms.end(),
							[&](const std::shared_ptr<Organism>& ptr){ return ptr.get() == other.get(); }
					));
				}
			} else {
				org -> move(pos);
			}
		}
		if (!reproduced) org->setPower(org->getPower() + 1);
		org -> setLiveLength(org->getLiveLength() - 1);
		if (org -> isDead()){
			org -> recordDeath(turn);
            organisms.erase(
				std::find_if(
					organisms.begin(), organisms.end(),
					[&](const std::shared_ptr<Organism>& ptr){ return ptr.get() == org.get(); }
			));
		}
	}
	turn++;

	// size_t i = 0;
	// while (i < organisms.size()) {
	// 	std::shared_ptr<Organism> org = organisms[i];

    //     std::vector<Position> possiblePositions = getVectorOfPossiblePositionsForOrganism(org);
	// 	std::vector<Position> freePositions = getVectorOfFreePositionsAround(org->getPosition());
    //     std::uniform_int_distribution<size_t> dist(0, possiblePositions.size() - 1);
    //     bool reproduced = false;

	// 	if (!freePositions.empty() && org->canReproduce()) {
	// 		Position pos = freePositions[dist(rng())];
	// 		std::shared_ptr<Organism> child = org->clone(pos, turn);
    //         addOrganismPtr(child);
	// 		org->setPower(org->getPower() / 2);
	// 		reproduced = true;
	// 	} else if (!possiblePositions.empty()) {
	// 		Position pos = possiblePositions[dist(rng())];
	// 		auto other = getOrganismFromPosition(pos.getX(), pos.getY());
	// 		if (other) {
	// 			org->collision(other);
	// 			auto it = std::find_if(
	// 				organisms.begin(), organisms.end(),
	// 				[&](auto const& ptr){ return ptr.get() == other.get(); }
	// 			);
	// 			size_t otherIdx = std::distance(organisms.begin(), it);
	// 			organisms.erase(it);
	// 			if (otherIdx < i) {
	// 				--i;
	// 			}
	// 		} else {
	// 			org -> move(pos);
	// 		}
	// 	}
	// 	if (!reproduced) org->setPower(org->getPower() + 1);
	// 	org -> setLiveLength(org->getLiveLength() - 1);
	// 	if (org -> isDead()){
	// 		org -> recordDeath(turn);
    //         organisms.erase(organisms.begin() + i);
	// 	} else i++;
	// }
	// turn++;
}

// void World::writeWorld(string fileName)
// {
// 	fstream my_file;
// 	my_file.open(fileName, ios::out | ios::binary);
// 	if (my_file.is_open()) {
// 		my_file.write((char*)&this->worldX, sizeof(int));
// 		my_file.write((char*)&this->worldY, sizeof(int));
// 		my_file.write((char*)&this->turn, sizeof(int));
// 		int orgs_size = this->organisms.size();
// 		my_file.write((char*)&orgs_size, sizeof(int));
// 		for (int i = 0; i < orgs_size; i++) {
// 			int data;
// 			data = this->organisms[i].getPower();
// 			my_file.write((char*)&data, sizeof(int));
// 			data = this->organisms[i].getPosition().getX();
// 			my_file.write((char*)&data, sizeof(int));
// 			data = this->organisms[i].getPosition().getY();
// 			my_file.write((char*)&data, sizeof(int));
// 			string s_data = this->organisms[i].getSpecies();
// 			int s_size = s_data.size();
// 			my_file.write((char*)&s_size, sizeof(int));
// 			my_file.write(s_data.data(), s_data.size());
// 		}
// 		my_file.close();
// 	}
// }

// void World::readWorld(string fileName)
// {
// 	fstream my_file;
// 	my_file.open(fileName, ios::in | ios::binary);
// 	if (my_file.is_open()) {
// 		int result;
// 		my_file.read((char*)&result, sizeof(int));
// 		this->worldX = (int)result;
// 		my_file.read((char*)&result, sizeof(int));
// 		this->worldY = (int)result;
// 		my_file.read((char*)&result, sizeof(int));
// 		this->turn = (int)result;
// 		my_file.read((char*)&result, sizeof(int));
// 		int orgs_size = (int)result;
// 		vector<Organism> new_organisms;
// 		for (int i = 0; i < orgs_size; i++) {
// 			int power;
// 			my_file.read((char*)&result, sizeof(int));
// 			power = (int)result;

// 			int pos_x;
// 			my_file.read((char*)&result, sizeof(int));
// 			pos_x = (int)result;
// 			int pos_y;
// 			my_file.read((char*)&result, sizeof(int));
// 			pos_y = (int)result;
// 			Position pos{ pos_x, pos_y };
			
// 			int s_size;
// 			my_file.read((char*)&result, sizeof(int));
// 			s_size = (int)result;

// 			string species;
// 			species.resize(s_size);
// 			my_file.read((char*)&species[0], s_size);
			
// 			Organism org(power, pos);
// 			org.setSpecies(species);
// 			new_organisms.push_back(org);
// 		}
// 		this->organisms = new_organisms;
// 		my_file.close();
// 	}
// }

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