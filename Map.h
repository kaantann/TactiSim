#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <cstddef>

enum class TileType
{
    UNKNOWN,   
    GRASS,     
    WATER,     
    OBSTACLE   
};

class Map
{
public:
    explicit Map(int numTilesX, int numTilesY, int tileSize);

    void draw(sf::RenderTarget& target) const;

    int getTileSize() const { return tileSize_; };
    sf::Vector2i getMapSizeInTiles() const { return mapSizeInTiles_; };
    sf::Vector2i getMapSizeInPixels() const { return sf::Vector2i{mapSizeInTiles_.x * tileSize_, mapSizeInTiles_.y * tileSize_}; };
    void setTile(int tileX, int tileY, TileType newType);


    bool isValidCoordinate(int tileX, int tileY) const;
    TileType getTileType(int tileX, int tileY) const;

    bool isWalkable(int tileX, int tileY) const;

    // Convert tile coordinate to the pixel coordinate of the tile's CENTER
    sf::Vector2f tileToPixelCenter(int tileX, int tileY) const;

    // Convert world pixel coordinate to the tile coordinate it falls within
    // Note: Can return coordinates outside map bounds if pixelCoords is off-map
    sf::Vector2i pixelToTile(const sf::Vector2f& pixelCoords) const;



private:
    void initializeGrid(); // Called by constructor
    size_t getIndex(int x, int y) const; // Calculates 1D index from 2D coords
    sf::Color getTileColor(TileType type) const; // Maps TileType to a visual Color
    void updateTileVisual(int tileX, int tileY, TileType type);


    // --- Members ---
    sf::Vector2i mapSizeInTiles_; // in [x,y] format
    int tileSize_;       // in pixels

    // Flat vector: access via getIndex(x,y)
    std::vector<TileType> gridData_;             // Stores the LOGICAL type of each tile
    std::vector<sf::RectangleShape> tileVisuals_; // Stores the VISUAL shape for each tile
};
