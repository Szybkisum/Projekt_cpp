#pragma once
#include "Organism.h"

class Animal : public Organism
{
    private:
        Position lastPosition;
    public:
        Animal(int power, int initiative, int liveLength, int powerToReproduce, Position position, int birthTurn);
        Animal(int power, int initiative, int liveLength, int powerToReproduce, Position position, int birthTurn, std::vector<std::shared_ptr<LifeRecord>> ancestorHistory);

        void move(Position position) override;
};