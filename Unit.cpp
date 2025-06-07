#include "Unit.h"


Unit::Unit(int id, UnitType type, Faction faction, const sf::Vector2f& position) :
	id_{id}, type_{type}, faction_{faction}, position_{position}
{
	setupVisuals();
}


void Unit::setupVisuals()
{
	float radius{10};
	shape_ = sf::CircleShape{radius};

	shape_.setOrigin({radius, radius});
	shape_.setFillColor(determineColor());
	shape_.setPosition(position_);
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
}

void Unit::update(float deltaTime)
{
	//TODO;
}


