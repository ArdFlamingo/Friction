#pragma once

#include <stdint.h>
#include <Arduboy2.h>

#include "Map.h"
#include "Maps.h"

class Game
{
private:
    uint8_t currentMapIndex = 0;

public:
    Arduboy2 arduboy;

    enum class GameState : uint8_t
    {
        Title,
        Game,
        Gameover
    };

    void setup();
    void loop();

    const Map & getCurrentMap() const
    {
        return maps[this->currentMapIndex];
    }

    // Selects the specified map, even if it's invalid
    void selectMap(uint8_t mapIndex)
    {
        this->currentMapIndex = mapIndex;
    }

    // A safer version of selectMap
    bool trySelectMap(uint8_t mapIndex)
    {
        if(mapIndex >= totalMaps)
            return false;

        this->currentMapIndex = mapIndex;
        return true;
    }

    // Selects the next map
    void selectNextMap()
    {
        if(this->currentMapIndex < lastMapIndex)
            ++this->currentMapIndex;
    }

    // Same as selectNextMap, but reports success
    bool trySelectNextMap()
    {
        if(this->currentMapIndex == lastMapIndex)
            return false;

        ++this->currentMapIndex;
        return true;
    }

private:
    void update();
    void updateGame();
    void drawMap();
};

extern Game game;