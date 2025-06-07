#pragma once

#include "Unit.h"
#include <vector>
#include <memory>   
#include <optional> 

class UnitManager
{
public:
    explicit UnitManager();

    int addUnit(UnitType type, Faction faction, const sf::Vector2f& position);

    Unit* getUnitById(int id);
    const std::vector<std::unique_ptr<Unit>>& getAllUnits() const;

    void updateAllUnits(float deltaTime);
    void drawAllUnits(sf::RenderTarget& target);

private:
    std::vector<std::unique_ptr<Unit>> units_;
    int nextUnitId_ {0}; //for unique ID generarion
};
