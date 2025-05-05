#pragma once
#include "Plant.h"

class Toadstool : public Plant
{
    public:
        Toadstool();
        Toadstool(Position position, int birthTurn);
        Toadstool(Position position, int birthTurn, std::vector<std::shared_ptr<LifeRecord>> ancestorHistory);
        std::shared_ptr<Organism> clone(const Position& pos, int birthTurn) const override;
};