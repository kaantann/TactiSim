#pragma once

#include <SFML/Graphics.hpp>
#include <string>

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
    void setPosition(const sf::Vector2f& pos) { position_ = pos; };
    int getID() const { return id_; };
    UnitType getType() const { return type_; };
    Faction getFaction() const { return faction_; };
    sf::FloatRect getBounds() const { return shape_.getGlobalBounds(); };

    void draw(sf::RenderTarget& target);
    virtual void update(float deltaTime);

protected: 
    int id_;
    UnitType type_;
    Faction faction_;
    sf::Vector2f position_;

    //sf::Sprite sprite_; // Or sf::CircleShape, sf::RectangleShape for simple representation
    sf::Texture texture_; // Each unit instance might have its own texture or share one

    // Example: Simple visual representation without sprites initially
    sf::CircleShape shape_; // Use this if you don't have sprites yet

private:
    void setupVisuals(); // Helper to set up shape_ or sprite_
    sf::Color determineColor();
};

