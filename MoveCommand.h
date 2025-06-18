#pragma once

#include "Command.h"

class MoveCommand : public Command
{
public:
    explicit MoveCommand(const sf::Vector2f& targetDestination);

    void start(Unit& unit) override;
    void update(Unit& unit, float deltaTime) override;
    bool isFinished() const override { return finished_; };

private:
    sf::Vector2f targetDestination_;
    bool finished_ = false;
    // float movementThreshold_ = 2.0f; // Distance to consider target reached
};

