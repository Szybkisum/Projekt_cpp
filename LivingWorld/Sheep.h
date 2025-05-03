#pragma once
#include "Animal.h"

class Sheep : public Animal
{
    public:
        Sheep(Position position, int birthTurn);
        Sheep(Position position, int birthTurn, std::vector<std::shared_ptr<LifeRecord>> ancestorHistory);
        std::shared_ptr<Organism> clone(const Position& pos, int birthTurn) const override;
};