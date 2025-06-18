#include "Unit.h"
#include "Command.h"

Unit::Unit(int id, UnitType type, Faction faction, const sf::Vector2f& position) :
	id_{id}, type_{type}, faction_{faction}, position_{position}, isSelected_{false}, selectionHighlight_{position}
{
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
		sf::Vector2f unitCenterPos = getPosition();
		sf::FloatRect unitBounds = getBounds();

		selectionHighlight_.setSize(sf::Vector2f(unitBounds.size.x * 1.05f, unitBounds.size.y * 1.05f));
		selectionHighlight_.setOrigin({selectionHighlight_.getSize().x / 2.0f, selectionHighlight_.getSize().y / 2.0f});
		selectionHighlight_.setPosition(unitCenterPos); // Position around the unit

		target.draw(selectionHighlight_);
	}
}


void Unit::update(float deltaTime)
{
	if (currentCommand_)
	{
		currentCommand_->update(*this, deltaTime);
		if (currentCommand_->isFinished())
		{
			currentCommand_.reset(); // Command is done, remove it
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


