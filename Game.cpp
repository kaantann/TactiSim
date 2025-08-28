#include "Config.h"
#include "Game.h"
#include "MoveCommand.h"
#include "AttackCommand.h"
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

	setupInitialUnits();
}

void Game::setupInitialUnits()
{
	Unit::Stats infantryStats{}; // Uses defaults
	Unit::Stats tankStats{200, 200, 25, 75.0f, 3.0f,200.0f}; // MaxHP, CurHP, Atk, AtkRange, Cooldown, VisionRange

	//Unit1
	sf::Vector2f unit1Pos = gameMap_.tileToPixelCenter(3, 3);
	if (gameMap_.isWalkable(3, 3))
	{ 
		unitManager_.addUnit(UnitType::INFANTRY, Faction::FRIENDLY, unit1Pos, infantryStats);
		std::cout << "Added FRIENDLY INFANTRY at tile (3,3) -> pixel " << unit1Pos.x << "," << unit1Pos.y << std::endl;
	}
	else
	{
		std::cout << "Could not place unit at tile (3,3) - not walkable." << std::endl;
	}

	//Unit2
	sf::Vector2f unit2Pos = gameMap_.tileToPixelCenter(10, 7);
	if (gameMap_.isWalkable(10, 7))
	{
		unitManager_.addUnit(UnitType::TANK, Faction::ENEMY, unit2Pos, tankStats);
		std::cout << "Added ENEMY TANK at tile (10,7) -> pixel " << unit2Pos.x << "," << unit2Pos.y << std::endl;
	}
	else
	{
		std::cout << "Could not place unit at tile (10,7) - not walkable." << std::endl;
	}


	//Unit3
	sf::Vector2f unit3Pos = gameMap_.tileToPixelCenter(5, 11);
	if (gameMap_.isWalkable(5, 11))
	{
		unitManager_.addUnit(UnitType::INFANTRY, Faction::ENEMY, unit3Pos, infantryStats);
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

	while (const auto& optEvent = window_.pollEvent())
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
				sf::Vector2i pixelPos{mouseButtonData->position.x, mouseButtonData->position.y};
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
					if (selectedUnit_ == nullptr || !selectedUnit_->isAlive())
						continue;

					sf::Vector2f targetPos(static_cast<float>(pixelPos.x), static_cast<float>(pixelPos.y));

					Unit* targetUnit = nullptr;
					// Check if the click was on another unit
					const auto& allUnits = unitManager_.getAllUnits();
					for (const auto& unitPtr : allUnits)
					{
						if (unitPtr && unitPtr.get() != selectedUnit_ && unitPtr->isAlive() && unitPtr->getBounds().contains(worldPos))
						{
							targetUnit = unitPtr.get();
							break;
						}
					}


					if (targetUnit && selectedUnit_->getFaction() != targetUnit->getFaction()) // Clicked on an enemy/different faction unit
					{
						selectedUnit_->setCommand(std::make_unique<AttackCommand>(targetUnit));
					}
					else if (!targetUnit || targetUnit == selectedUnit_ || selectedUnit_->getFaction() == targetUnit->getFaction()) // Clicked on empty space, self, or friendly unit: issue MoveCommand
					{
						sf::Vector2i targetTileCoords{gameMap_.pixelToTile(worldPos)};
						if (gameMap_.isValidCoordinate(targetTileCoords.x, targetTileCoords.y) && gameMap_.isWalkable(targetTileCoords.x, targetTileCoords.y))
						{
							sf::Vector2f targetPixelPosAtTileCenter{gameMap_.tileToPixelCenter(targetTileCoords.x, targetTileCoords.y)};
							selectedUnit_->setCommand(std::make_unique<MoveCommand>(targetPixelPosAtTileCenter));
						}
					}
				}
			}
		}
	}
}

void Game::update(sf::Time deltaTime)
{
	auto dt{deltaTime.asSeconds()};

	unitManager_.processAI(dt);
	unitManager_.updateAllUnits(dt);
	unitManager_.cleanupDestroyedUnits();
}

void Game::render()
{
	window_.clear(sf::Color(20, 20, 20));

	// Draw elements in order (background to foreground)
	gameMap_.draw(window_);
	unitManager_.drawAllUnits(window_);


	// Potentially draw UI elements here in later phases

	window_.display();
}