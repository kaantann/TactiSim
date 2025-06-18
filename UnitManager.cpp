#include "UnitManager.h"

UnitManager::UnitManager()
	: nextUnitId_{0},units_{}
{

}

int UnitManager::addUnit(UnitType type, Faction faction, const sf::Vector2f& position)
{
	auto newUnit{std::make_unique<Unit>(nextUnitId_++,type,faction,position)};
	units_.push_back(std::move(newUnit));
	return nextUnitId_;
}

Unit* UnitManager::getUnitById(int id)
{
	for (auto& unit : units_)
	{
		if (id == unit->getID())
		{
			return unit.get();
		}
	}

	return nullptr;
}

const std::vector<std::unique_ptr<Unit>>& UnitManager::getAllUnits() const
{
	return units_;
}

void UnitManager::updateAllUnits(float deltaTime)
{
	for (auto& unit : units_)
	{
		unit->update(deltaTime);
	}
}

void UnitManager::drawAllUnits(sf::RenderTarget& target)
{
	for (auto& unit : units_)
	{
		unit->draw(target);
	}
}




