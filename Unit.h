#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "Command.h"

class UnitManager; // Forward declaration

enum class UnitType
{
	NONE,
	INFANTRY,
	TANK,
};

enum class Faction
{
	NONE,
	FRIENDLY,
	ENEMY,
	NEUTRAL,
};

class Unit
{
public:
	struct Stats
	{
		int maxHealth{150};
		int currentHealth{150};
		int attackPower{10};
		float attackRange{50.0f}; // In pixels (or tiles if I change range system)
		float attackCooldown{2.0f}; // Seconds between attacks
		float visionRange {200.0f}; // in Pixels
		// float defense = 0.0f; // Optional
	};


	explicit Unit(int id, UnitType type, Faction faction, const sf::Vector2f& position, const Stats& initialStats = {});
	virtual ~Unit() = default;

	const sf::Vector2f& getPosition() const { return position_; };
	void setPosition(const sf::Vector2f& pos) { position_ = pos; shape_.setPosition(position_); };
	int getID() const { return id_; };
	UnitType getType() const { return type_; };
	Faction getFaction() const { return faction_; };
	sf::FloatRect getBounds() const { return shape_.getGlobalBounds(); };
	void setSelected(bool selected) { isSelected_ = selected; };
	bool isSelected() const { return isSelected_; };
	void setCommand(std::unique_ptr<Command> command);
	float getSpeed() const { return speed_; };
	const Stats& getStats() const { return stats_; }
	int getCurrentHealth() const { return stats_.currentHealth; }
	bool isAlive() const { return isAlive_; }
	float getAttackRange() const { return stats_.attackRange; }
	bool hasCommand() const { return currentCommand_ != nullptr; };

	void draw(sf::RenderTarget& target);
	virtual void update(float deltaTime);



	void takeDamage(int amount);
	bool canAttack() const;
	void resetAttackTimer();
	void updateAttackTimer(float deltaTime);

protected:
	int id_;
	UnitType type_;
	Faction faction_;
	sf::Vector2f position_;

	bool isSelected_;
	sf::RectangleShape selectionHighlight_; // Or sf::CircleShape, etc.

	//sf::Sprite sprite_; // Or sf::CircleShape, sf::RectangleShape for simple representation
	sf::Texture texture_; // Each unit instance might have its own texture or share one

	// Example: Simple visual representation without sprites initially
	sf::CircleShape shape_; // Use this if you don't have sprites yet

	std::unique_ptr<Command> currentCommand_{nullptr};
	float speed_{100.0f}; // Pixels per second, adjust as needed


	Stats stats_;
	float currentAttackCooldown_{0.0f}; // Time remaining until next attack is possible
	bool isAlive_{true};

private:
	void setupVisuals(); // Helper to set up shape_ or sprite_
	void setupSelectionVisual();
	sf::Color determineColor();
};

