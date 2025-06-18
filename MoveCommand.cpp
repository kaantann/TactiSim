#include "MoveCommand.h"
#include "Unit.h"
#include <cmath>
// #include <iostream> // For debug

MoveCommand::MoveCommand(const sf::Vector2f& targetDestination) :
    targetDestination_{targetDestination},
    finished_{false}
{
    
}

void MoveCommand::start(Unit& unit)
{
    // Potentially set an 'isMoving' flag on the unit if needed
    finished_ = false; // Reset finished state in case command is reused
}

void MoveCommand::update(Unit& unit, float deltaTime)
{
    if (finished_) 
        return;

    sf::Vector2f currentPosition {unit.getPosition()};
    sf::Vector2f direction{targetDestination_ - currentPosition};
    float distance{std::sqrt(direction.x * direction.x + direction.y * direction.y)};

    float movementThreshold{unit.getSpeed() * deltaTime * 0.5f}; // Stop if very close
    if (distance < movementThreshold || distance < 1.0f)
    { // If very close or reached target
        unit.setPosition(targetDestination_); // Snap to exact target
        finished_ = true;
        return;
    }

    // Normalize direction vector
    direction.x /= distance;
    direction.y /= distance;

    sf::Vector2f movement {direction * unit.getSpeed() * deltaTime};
    unit.setPosition(currentPosition + movement);
}