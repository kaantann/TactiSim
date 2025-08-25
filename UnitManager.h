#pragma once

#include "Unit.h"
#include <vector>
#include <memory>   
#include <optional> 

class UnitManager
{
public:
    explicit UnitManager();
    UnitManager(const UnitManager&) = delete;
    UnitManager& operator=(const UnitManager&) = delete;

    UnitManager(UnitManager&&) = default;
    UnitManager& operator=(UnitManager&&) = default; 

    int addUnit(UnitType type, Faction faction, const sf::Vector2f& position, const Unit::Stats& initialStats);

    Unit* getUnitById(int id);
    const std::vector<std::unique_ptr<Unit>>& getAllUnits() const;

    void updateAllUnits(float deltaTime);
    void processAI(float deltaTime);
    void drawAllUnits(sf::RenderTarget& target);

    void cleanupDestroyedUnits();

private:
    int nextUnitId_{0}; //for unique ID generarion
    std::vector<std::unique_ptr<Unit>> units_;

    // Optional AI helper function, could be private or in the .cpp file
    Unit* findBestTargetFor(const Unit* aiUnit);

};
