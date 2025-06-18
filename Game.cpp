#include "Config.h"
#include "Game.h"
#include "MoveCommand.h"
#include <iostream> // For debug output

Game::Game() :
	window_{sf::VideoMode{sf::Vector2u{WINDOW_WIDTH, WINDOW_HEIGHT}},WINDOW_TITLE, sf::Style::Titlebar | sf::Style::Close},
	gameMap_{MAP_TILES_X, MAP_TILES_Y, TILE_SIZE},
	unitManager_{}
{
	// Can limit framerate for smoother updates and less CPU usage - off for now
	// window_.setFramerateLimit(60);

	// Enable vertical sync
	// window_.setVerticalSyncEnabled(true);

	std::cout << "Game initialized." << std::endl;
	std::cout << "Map created: " << gameMap_.getMapSizeInTiles().x << "x"
		<< gameMap_.getMapSizeInTiles().y << " tiles, "
		<< TILE_SIZE << "px per tile." << std::endl;
	std::cout << "Window size: " << window_.getSize().x << "x" << window_.getSize().y << " pixels." << std::endl;

	// Place some initial units for testing Phase 1
	setupInitialUnits();
}

void Game::setupInitialUnits()
{
	// Example: Place a friendly infantry unit near the top-left
	sf::Vector2f unit1Pos = gameMap_.tileToPixelCenter(3, 3);
	if (gameMap_.isWalkable(3, 3))
	{ // Check if tile is walkable before placing
		unitManager_.addUnit(UnitType::INFANTRY, Faction::FRIENDLY, unit1Pos);
		std::cout << "Added FRIENDLY INFANTRY at tile (3,3) -> pixel " << unit1Pos.x << "," << unit1Pos.y << std::endl;
	}
	else
	{
		std::cout << "Could not place unit at tile (3,3) - not walkable." << std::endl;
	}


	// Example: Place an enemy tank unit further into the map
	sf::Vector2f unit2Pos = gameMap_.tileToPixelCenter(10, 7);
	if (gameMap_.isWalkable(10, 7))
	{
		unitManager_.addUnit(UnitType::TANK, Faction::ENEMY, unit2Pos);
		std::cout << "Added ENEMY TANK at tile (10,7) -> pixel " << unit2Pos.x << "," << unit2Pos.y << std::endl;
	}
	else
	{
		std::cout << "Could not place unit at tile (10,7) - not walkable." << std::endl;
	}


	// Example: Place another friendly unit
	sf::Vector2f unit3Pos = gameMap_.tileToPixelCenter(5, 11);
	if (gameMap_.isWalkable(5, 11))
	{
		unitManager_.addUnit(UnitType::INFANTRY, Faction::ENEMY, unit3Pos);
		std::cout << "Added FRIENDLY INFANTRY at tile (5,11) -> pixel " << unit3Pos.x << "," << unit3Pos.y << std::endl;
	}
	else
	{
		std::cout << "Could not place unit at tile (5,11) - not walkable." << std::endl;
	}
}

/*
* Game logic starts from here
*/


void Game::run()
{
	sf::Clock clock{};

	while (window_.isOpen())
	{
		sf::Time deltaTime = clock.restart(); // Get time elapsed since last frame

		processEvents();
		update(deltaTime);
		render();
	}
}

void Game::processEvents()
{

	while (const auto optEvent = window_.pollEvent())
	{
		if (optEvent->is<sf::Event::Closed>() ||
			(optEvent->is<sf::Event::KeyPressed>() && optEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape))
			window_.close();
		else if (optEvent->is<sf::Event::Resized>())
		{
			if (const auto* resizedData = optEvent->getIf<sf::Event::Resized>())
			{
				// Update the view to match the new window size to prevent distortion/stretching
				auto a = resizedData->size;
				sf::Vector2f vector{static_cast<float>(a.x),static_cast<float>(a.y)};

				sf::FloatRect visibleArea{{0.f,0.f},vector};
				window_.setView(sf::View(visibleArea));
			}
		}
		else if (optEvent->is<sf::Event::MouseButtonPressed>())
		{
			if (const auto* mouseButtonData = optEvent->getIf<sf::Event::MouseButtonPressed>())
			{
				sf::Vector2i pixelPos = {mouseButtonData->position.x, mouseButtonData->position.y};
				// Convert pixelPos to world coordinates if you use a view/camera
				// For now, assuming 1:1 view:
				sf::Vector2f worldPos(static_cast<float>(pixelPos.x), static_cast<float>(pixelPos.y));

				if (mouseButtonData->button == sf::Mouse::Button::Left)
				{
					bool unitClicked{false};
					auto& allUnits{unitManager_.getAllUnits()};
					for (auto& unitPtr : allUnits)
					{
						Unit* unit{unitPtr.get()};
						if (unit && unit->getBounds().contains(worldPos))
						{
							if (selectedUnit_)
							{
								selectedUnit_->setSelected(false); // Deselect old unit
							}
							selectedUnit_ = unit;
							selectedUnit_->setSelected(true);
							unitClicked = true;
							break; // Select only one unit for now
						}
					}
					if (!unitClicked && selectedUnit_)
					{
						selectedUnit_->setSelected(false);
						selectedUnit_ = nullptr; // Deselect if clicked on empty space
					}
				}
				else if (mouseButtonData->button == sf::Mouse::Button::Right)
				{
					if (selectedUnit_)
					{
						sf::Vector2f targetPos(static_cast<float>(pixelPos.x), static_cast<float>(pixelPos.y));
						selectedUnit_->setCommand(std::make_unique<MoveCommand>(targetPos));
					}
				}
			}
		}
	}
}

void Game::update(sf::Time deltaTime)
{
	// For current phase, units don't have individual update logic yet,
	// but we call it for consistency and future expansion.
	unitManager_.updateAllUnits(deltaTime.asSeconds());
}

void Game::render()
{
	window_.clear(sf::Color(20, 20, 20));

	// Draw game elements in order (background to foreground)
	gameMap_.draw(window_);
	unitManager_.drawAllUnits(window_);


	// Potentially draw UI elements here in later phases

	window_.display();
}