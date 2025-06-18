#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "Command.h"

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
    explicit Unit(int id, UnitType type, Faction faction, const sf::Vector2f& position);
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
    float getSpeed() const {return speed_;};

    void draw(sf::RenderTarget& target);
    virtual void update(float deltaTime);

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

private:
    void setupVisuals(); // Helper to set up shape_ or sprite_
    void setupSelectionVisual();
    sf::Color determineColor();
};

