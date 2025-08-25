#include "AttackCommand.h"
#include "Unit.h"
#include <cmath>   

AttackCommand::AttackCommand(Unit* target) :
    targetUnit_{target}, commandIssuedAttack_{false}
{
    // if (targetUnit_) std::cout << "AttackCommand created for target ID: " << targetUnit_->getID() << std::endl;
    // else std::cout << "AttackCommand created with NULL target!" << std::endl;
}

void AttackCommand::start(Unit& unit)
{
    commandIssuedAttack_ = false;
    // The command doesn't "finish" until the target is dead, out of range, or the attacker is given a new command.
}

void AttackCommand::update(Unit& attacker, float deltaTime)
{
    if (!targetUnit_ || !targetUnit_->isAlive() || !attacker.isAlive())
    {
        // Target is dead/invalid or attacker is dead, command is effectively finished for practical purposes
        // but isFinished() might handle this differently depending on design.
        // For now, let the Unit's command queue clear it if isFinished returns true.
        return;
    }

    sf::Vector2f attackerPos = attacker.getPosition();
    sf::Vector2f targetPos = targetUnit_->getPosition();
    sf::Vector2f direction = targetPos - attackerPos;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance <= attacker.getAttackRange())
    {
        // Target is in range
        if (attacker.canAttack())
        {
            // std::cout << "Unit " << attacker.getID() << " attacks Unit " << targetUnit_->getID() << std::endl;
            targetUnit_->takeDamage(attacker.getStats().attackPower);
            attacker.resetAttackTimer(); // Start cooldown
            commandIssuedAttack_ = true; // Mark that an attack was attempted/made in this command context

            // If target dies from this attack, the command could be considered finished.
        }
        // If target is in range but attacker is on cooldown, do nothing this frame regarding attack.
        // The unit might still turn to face the target, or a move command might make it reposition.
    }
    else
    {
        // Target is out of range. What should the attacker do?
        // Option 1: Command finishes (simplest for now).
        // Option 2: Attacker moves towards target (requires creating a MoveCommand internally or a more complex, like "AttackMoveCommand"? (¬_¬") ).
        // For now, let's keep it simple: if target moves out of range, the attack command won't fire.
        // Or the user would need to issue a new command (move or attack again).
        // commandIssuedAttack_ = false; // Reset if you want it to re-attempt attack if target comes back in range
    }
}

bool AttackCommand::isFinished() const
{
    // When is an attack command "finished"?
    // 1. Target is dead.
    // 2. Attacker is dead (handled by Unit::update early exit).
    // 3. (Optional) If target moves out of initial attack range and we don't chase.
    // 4. If the attacker is given a new command (handled by Unit::setCommand).


    if (!targetUnit_ || !targetUnit_->isAlive())
    {
        return true; // Target is gone or dead
    }
    // If we want the command to "finish" after one successful attack attempt:
    // return commandIssuedAttack_; 

    // For continuous attack as long as target is alive & in range (and attacker can fire):
    return false; // The command persists as long as the target is a valid, living entity.
    // The Unit class will clear it if a new command is set.
    // If target moves out of range, this command remains but won't trigger attacks
    // until target is back in range or a new command is issued.
}
