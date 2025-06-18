#pragma once

#include <SFML/System/Vector2.hpp> 

class Unit; // Forward declaration to avoid circular dependency

class Command
{
public:
    virtual ~Command() = default;

    // Called once when the command is assigned to a unit
    virtual void start(Unit& unit) = 0;

    // Called every frame to update the command's progress
    virtual void update(Unit& unit, float deltaTime) = 0;

    // Returns true if the command has finished its execution
    virtual bool isFinished() const = 0;
};
