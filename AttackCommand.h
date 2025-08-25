#pragma once

#include "Command.h"
// Unit.h will be included in .cpp; forward declare if needed by pointer/ref here
// class Unit; 

class AttackCommand : public Command
{
public:
    // Constructor takes a pointer to the target Unit.
    // Using a raw pointer here. The command issuer needs to ensure target validity.
    // Alternatively, use std::weak_ptr if units are managed by shared_ptr,
    // or an ID if units are globally managed and retrievable by ID.
    // For simplicity with unique_ptr in UnitManager, raw pointer is okay if command lifetime is short.
    AttackCommand(Unit* target);

    void start(Unit& unit) override;
    void update(Unit& unit, float deltaTime) override;
    bool isFinished() const override;

private:
    Unit* targetUnit_;
    bool commandIssuedAttack_ = false; // To ensure attack happens once per reasonable interval if target stays in range
    // bool finished_ = false; // Command might be ongoing if target is alive and attacker can keep attacking
};

