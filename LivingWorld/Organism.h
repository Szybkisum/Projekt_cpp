#pragma once
#include <memory>
#include <vector>
#include "Position.h"
#include "LifeRecord.h"

class Organism
{
private:
	int power;
	int initiative;
	int liveLength;
	int powerToReproduce;
	Position position;
	std::string species;
	std::shared_ptr<LifeRecord> lifeRecord;
	std::vector<std::shared_ptr<LifeRecord>> ancestorHistory;
public:
	Organism(int power, int initiative, int liveLength, int powerToReproduce, Position position, int birthTurn);
	Organism(int power, int initiative, int liveLength, int powerToReproduce, Position position, int birthTurn, std::vector<std::shared_ptr<LifeRecord>> ancestorHistory);	

	Organism(const Organism&) = default;
    Organism(Organism&&) noexcept = default;
    Organism& operator=(const Organism&) = default;
    Organism& operator=(Organism&&) noexcept = default;
    virtual ~Organism() = default;

	int getPower() const;
	void setPower(int power);
	int getInitiative() const;
	int getLiveLength() const;
	void setLiveLength(int liveLength);
	Position getPosition() const;
	void setPosition(Position position);
	std::string getSpecies() const;
	void setSpecies(std::string species);
	const std::vector<std::shared_ptr<LifeRecord>>& getAncestorHistory() const;

	std::string toString() const;
	bool canReproduce() const;
	bool isDead() const;
	void recordDeath(int turn);

	virtual std::shared_ptr<Organism> clone(const Position& pos, int birthTurn) const = 0;
	virtual void move(int dx, int dy) = 0;
};