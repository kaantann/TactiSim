#include "Unit.h"
#include "Command.h"

Unit::Unit(int id, UnitType type, Faction faction, const sf::Vector2f& position, const Stats& initialStats) :
	id_{id}, type_{type}, faction_{faction}, position_{position}, isSelected_{false}, 
	selectionHighlight_{position}, stats_{initialStats},isAlive_{true},currentAttackCooldown_{0.0f}
{
	if (stats_.currentHealth > stats_.maxHealth || stats_.currentHealth <= 0 && stats_.maxHealth > 0)
	{
		stats_.currentHealth = stats_.maxHealth;
	}

	setupVisuals();
	setupSelectionVisual();
}


void Unit::setupVisuals()
{
	float radius{10};
	shape_ = sf::CircleShape{radius};

	shape_.setOrigin({radius, radius});
	shape_.setFillColor(determineColor());
	shape_.setPosition(position_);
}

void Unit::setupSelectionVisual()
{
	selectionHighlight_.setFillColor(sf::Color::Transparent);
	selectionHighlight_.setOutlineColor(sf::Color::Black);
	selectionHighlight_.setOutlineThickness(2.0f);
}

sf::Color Unit::determineColor()
{
	switch (faction_)
	{
		case Faction::FRIENDLY: return sf::Color::Green;
		case Faction::ENEMY:    return sf::Color::Red;
		case Faction::NEUTRAL:  return sf::Color::Yellow;

		case Faction::NONE:
		default:                return sf::Color::Magenta;
	}
}

void Unit::draw(sf::RenderTarget& target)
{
	target.draw(shape_);

	if (isSelected_)
	{
		// Update highlight position to match unit's current position
		// Assuming highlight's origin and unit's origin are handled consistently
		sf::FloatRect unitBounds = getBounds();

		selectionHighlight_.setSize(sf::Vector2f(unitBounds.size.x * 1.05f, unitBounds.size.y * 1.05f));				// These lines could be removed since unit size is a constant value. no need to recalculate and set again.
		selectionHighlight_.setOrigin({selectionHighlight_.getSize().x / 2.0f, selectionHighlight_.getSize().y / 2.0f});// These lines could be removed since unit size is a constant value. no need to recalculate and set again.
		selectionHighlight_.setPosition(position_); // Position around the unit

		target.draw(selectionHighlight_);
	}
}

void Unit::update(float deltaTime)
{
	if (!isAlive_) 
		return;

	updateAttackTimer(deltaTime);

	if (currentCommand_)
	{
		currentCommand_->update(*this, deltaTime);
		if (currentCommand_->isFinished())
		{
			currentCommand_.reset();
		}
	}
}

void Unit::setCommand(std::unique_ptr<Command> command)
{
	currentCommand_ = std::move(command);
	if (currentCommand_)
	{
		currentCommand_->start(*this);
	}
}

void Unit::takeDamage(int amount)
{
	if (!isAlive_) 
		return;

	// Optional: apply defense calculation here
	// int actualDamage = amount - stats_.defense;
	// if (actualDamage < 0) 
	//	actualDamage = 0;
	int actualDamage = amount; // Simple for now

	stats_.currentHealth -= actualDamage;
	// std::cout << "Unit " << id_ << " took " << actualDamage << " damage. Health: " << stats_.currentHealth << std::endl;

	if (stats_.currentHealth <= 0)
	{
		stats_.currentHealth = 0;
		isAlive_ = false;
		// std::cout << "Unit " << id_ << " has been destroyed." << std::endl;
		// I could change sprite to a "destroyed" state or play an animation/sound here
		// For now, it will just stop participating and be marked for removal by UnitManager
	}
}

void Unit::resetAttackTimer()
{
	currentAttackCooldown_ = stats_.attackCooldown;
}

bool Unit::canAttack() const
{
	return isAlive_ && currentAttackCooldown_ <= 0.0f;
}

void Unit::updateAttackTimer(float deltaTime)
{
	if (currentAttackCooldown_ > 0.0f)
	{
		currentAttackCooldown_ -= deltaTime;
		if (currentAttackCooldown_ < 0.0f)
		{
			currentAttackCooldown_ = 0.0f;
		}
	}
}




