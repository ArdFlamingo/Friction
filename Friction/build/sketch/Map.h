#line 1 "/Users/om/Downloads/ARDUBOY/Friction/Map.h"
#pragma once

// For uint8_t
#include <stdint.h>

// For pgm_read_byte
#include <avr/pgmspace.h>

// For TileType
#include "TileType.h"

// Represents a map stored in progmem
class Map
{
private:
	// Just a pointer, not an array
	const TileType * data = nullptr;
	
	// The dimensions of the loaded map
	uint8_t width = 0;
	uint8_t height = 0;

public:
	// A default constructor that uses the default values
	constexpr Map() = default;

	// A three argument constructor, to be explicitly given values
	constexpr Map(const TileType * data, uint8_t width, uint8_t height) :
		data { data },
		width { width },
		height { height }
	{
	}
	
	// Template voodoo to infer an array's dimensions
	template<uint8_t width, uint8_t height>
	constexpr Map(const TileType (&data)[height][width]) :
		Map(&data[0][0], width, height)
	{
	}
	
	// Determines if the map is null
	// (You probably won't need this, but just in case)
	constexpr bool isNull() const
	{
		return (this->data == nullptr);
	}
	
	// Get the width of the map
	constexpr uint8_t getWidth() const
	{
		return this->width;
	}
	
	// Get the height of the map
	constexpr uint8_t getHeight() const
	{
		return this->height;
	}
	
	// Gets the tile at the specified coordinates
	TileType getTile(int16_t x, int16_t y) const
	{
		// If the coordinate is out of bounds
		if(this->outOfBounds(x, y))
			// Assume it to be a sky tile
			return TileType::Sky;
			
		// Get address of tile in progmem
		const TileType * const pointer = &this->data[getIndex(x, y)];
		
		// Read byte from progmem
		const uint8_t byte = pgm_read_byte(pointer);
		
		// Convert to tile and return
		return static_cast<TileType>(byte);
	}
	
private:
	// Determine if a coordinate is out of bounds
	constexpr bool outOfBounds(int16_t x, int16_t y) const
	{
		return ((x < 0) || (y < 0) || (x >= this->width) || (y >= this->height));
	}

	// Get the flat index that corresponds to the 2D coordinate
	constexpr size_t getIndex(uint8_t x, uint8_t y) const
	{
		return ((y * this->width) + x);
	}
};