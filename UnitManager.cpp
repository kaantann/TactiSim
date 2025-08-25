#include "UnitManager.h"
#include "AttackCommand.h"
#include <algorithm>

UnitManager::UnitManager()
	: nextUnitId_{0}, units_{}
{

}

int UnitManager::addUnit(UnitType type, Faction faction, const sf::Vector2f& position, const Unit::Stats& initialStats)
{
	auto newUnit{std::make_unique<Unit>(nextUnitId_++,type,faction,position,initialStats)};
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

void UnitManager::processAI(float deltaTime)
{
	for (auto& unitPtr : units_)
	{
		Unit* unit = unitPtr.get();

		// Conditions for AI to take over:
		// 1. Unit is not null and is alive.
		// 2. Unit belongs to the ENEMY faction.
		// 3. Unit is currently IDLE (has no command).
		if (unit && unit->isAlive() && unit->getFaction() == Faction::ENEMY && !unit->hasCommand())
		{
			Unit* target = findBestTargetFor(unit);
			if (target)
			{
				unit->setCommand(std::make_unique<AttackCommand>(target));
			}
		}
	}
}

void UnitManager::drawAllUnits(sf::RenderTarget& target)
{
	for (auto& unit : units_)
	{
		unit->draw(target);
	}
}

void UnitManager::cleanupDestroyedUnits()
{
	units_.erase(
		std::remove_if(units_.begin(), units_.end(),
			[](const std::unique_ptr<Unit>& unit)
	{
		return !unit || !unit->isAlive();
	}),
		units_.end()
	);
}

Unit* UnitManager::findBestTargetFor(const Unit* unit)
{
	if (!unit)
		return nullptr;

	Unit* bestTarget = nullptr;
	const auto& aiStats = unit->getStats();
	float minDistanceSq = aiStats.visionRange * aiStats.visionRange + 1.0f;

	for (const auto& otherUnitPtr : units_)
	{
		Unit* potentialTargetUnit = otherUnitPtr.get();

		if (!potentialTargetUnit || potentialTargetUnit == unit || !potentialTargetUnit->isAlive() || potentialTargetUnit->getFaction() == unit->getFaction())
		{
			continue; // Skip self, dead, null, or friendly units
		}

		// Direction to potential target
		sf::Vector2f dirToPotential = potentialTargetUnit->getPosition() - unit->getPosition();
		float distSqToPotential = (dirToPotential.x * dirToPotential.x) + (dirToPotential.y * dirToPotential.y);

		//					Is target in vision?							and					Is target in attack range?
		if (distSqToPotential <= (aiStats.visionRange * aiStats.visionRange) && distSqToPotential <= (aiStats.attackRange * aiStats.attackRange))
		{
			minDistanceSq = distSqToPotential;
			bestTarget = potentialTargetUnit;
		}
	}

	return bestTarget;
}






