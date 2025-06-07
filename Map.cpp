#include "Map.h"
#include <stdexcept>
#include <iostream>

Map::Map(int numTilesX, int numTilesY, int tileSize) :
    mapSizeInTiles_{numTilesX, numTilesY},
    tileSize_{tileSize}
{
    if (numTilesX == 0 || numTilesY == 0 || tileSize == 0)
    {
        std::cerr << "ERROR: Map dimensions or tile size cannot be zero!" << std::endl;
        return;
    }

    initializeGrid();
}

sf::Color Map::getTileColor(TileType type) const
{
    switch (type)
    {
        case TileType::GRASS:    return sf::Color(50, 150, 50);  // Greenish
        case TileType::WATER:    return sf::Color(50, 50, 180);  // Blueish
        case TileType::OBSTACLE: return sf::Color(100, 100, 100); // Gray
        case TileType::UNKNOWN:
        default:                 return sf::Color::Magenta; // Error color
    }
}

void Map::updateTileVisual(int tileX, int tileY, TileType type)
{
    if (!isValidCoordinate(tileX, tileY)) 
        return;

    size_t index = getIndex(tileX, tileY);
    if (index < tileVisuals_.size())
    {
        tileVisuals_[index].setFillColor(getTileColor(type));
    }
}




void Map::initializeGrid()
{
    size_t totalTiles = static_cast<size_t>(mapSizeInTiles_.x) * mapSizeInTiles_.y;
    gridData_.resize(totalTiles);
    tileVisuals_.reserve(totalTiles);

    for (int y = 0; y < mapSizeInTiles_.y; ++y)
    {
        for (int x = 0; x < mapSizeInTiles_.x; ++x)
        {
            TileType type = TileType::GRASS;

            // Add some variety for testing
            if (x == 0 || y == 0 || x == mapSizeInTiles_.x - 1 || y == mapSizeInTiles_.y - 1)
                type = TileType::OBSTACLE; // Border
            else if ((x % 5 == 0) && (y % 4 == 0))
                type = TileType::WATER;


            gridData_[getIndex(x, y)] = type;

            //Create the visual representation
            sf::RectangleShape shape{sf::Vector2f{static_cast<float>(tileSize_), static_cast<float>(tileSize_)}};
            shape.setPosition(sf::Vector2f{static_cast<float>(x * tileSize_), static_cast<float>(y * tileSize_)});
            shape.setFillColor(getTileColor(type));

            //In order to see the grid structure clearly
            auto grayish = sf::Color(30, 30, 30);
            shape.setOutlineColor(grayish);
            shape.setOutlineThickness(-0.5f); // negative for inward outline

            tileVisuals_.push_back(shape);
        }
    }
}


void Map::draw(sf::RenderTarget& target) const
{
    // maybe I can use sf::VertexArray for performance issue
    for (const auto& shape : tileVisuals_)
    {
        target.draw(shape);
    }
}

#pragma region Utility
bool Map::isValidCoordinate(int tileX, int tileY) const
{
    return tileX >= 0 && tileX < mapSizeInTiles_.x &&
           tileY >= 0 && tileY < mapSizeInTiles_.y;
}

TileType Map::getTileType(int tileX, int tileY) const
{
    if (!isValidCoordinate(tileX, tileY))
    {
        return TileType::UNKNOWN;
    }
    return gridData_[getIndex(tileX, tileY)];
}

bool Map::isWalkable(int tileX, int tileY) const
{
    // For now, only GRASS is walkable
    TileType type = getTileType(tileX, tileY); // includes bounds check
    return (type == TileType::GRASS);
}

#pragma endregion

#pragma region Conversions
sf::Vector2f Map::tileToPixelCenter(int tileX, int tileY) const
{
    // Returns Magenta vector if invalid? Or clamp? Let's return 0,0 for now.
    if (!isValidCoordinate(tileX, tileY)) 
        return sf::Vector2f(0.f, 0.f);

    // Calculate center position
    float halfTile = static_cast<float>(tileSize_) / 2.0f;
    return sf::Vector2f(
        static_cast<float>(tileX * tileSize_) + halfTile,
        static_cast<float>(tileY * tileSize_) + halfTile
    );
}

sf::Vector2i Map::pixelToTile(const sf::Vector2f& pixelCoords) const
{
    if (tileSize_ == 0) 
        return sf::Vector2i(-1, -1);

    // Simple integer division truncates towards zero
    return sf::Vector2i(
        static_cast<int>(pixelCoords.x / tileSize_),
        static_cast<int>(pixelCoords.y / tileSize_)
    );
    // Note: caller should use isValidCoordinate() on the result if needed.
}
#pragma endregion

#pragma region Getters & Setters
// Calculate 1D index 
// Assumes coordinates are already validated!
size_t Map::getIndex(int x, int y) const
{
    return static_cast<size_t>(y) * mapSizeInTiles_.x + static_cast<size_t>(x);
}

void Map::setTile(int tileX, int tileY, TileType newType)
{
    if (!isValidCoordinate(tileX, tileY)) 
        return;

    size_t index = getIndex(tileX, tileY);
    gridData_[index] = newType;
    updateTileVisual(tileX, tileY, newType);
}
#pragma endregion
