#pragma once
#include "Plant.h"

class Grass : public Plant
{
    public:
        Grass(Position position, int birthTurn);
        Grass(Position position, int birthTurn, std::vector<std::shared_ptr<LifeRecord>> ancestorHistory);
        std::shared_ptr<Organism> clone(const Position& pos, int birthTurn) const override;
};