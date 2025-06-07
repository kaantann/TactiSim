#pragma once

#include <SFML/Graphics.hpp>
#include "Map.h"
#include "UnitManager.h"

class Game
{
public:
	explicit Game();

	void run();

private:
	void setupInitialUnits();
	void processEvents(); // To handle SFML events (input, window close, etc.)
	void update(sf::Time deltaTime);
	void render();


	//Fields
	sf::RenderWindow window_;      
	Map gameMap_;                  
	UnitManager unitManager_;      




};

