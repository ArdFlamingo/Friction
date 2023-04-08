#pragma once
#include <stdint.h>

enum class TileType : uint8_t
{
    Sky,
    Ground,
    GroundLeft,
    GroundRight,
    Tube,
    Cap,
    LeftWall,
    RightWall,
    PixelBoth,
    PixelLeft,
    PixelRight,
    LeftWallRightPixel,
    RightWallLeftPixel,
	Block,
	SidewaysTube,
	LeftCap,
	RightCap,
};

constexpr uint8_t tileWidth = 8;
constexpr uint8_t tileHeight = 8;

constexpr uint8_t halfTileWidth = 4;
constexpr uint8_t halfTileHeight = 4;

constexpr uint8_t getTileIndex(TileType tileType)
{
    return static_cast<uint8_t>(tileType);
}

inline TileType readTileTypeFromProgmem(const TileType * progmem)
{
	  return static_cast<TileType>(pgm_read_byte(progmem));
}

constexpr bool isSolid(TileType tileType)
{
	  return (tileType != TileType::Sky);
}
