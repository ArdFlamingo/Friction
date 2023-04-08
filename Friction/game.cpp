#include "game.h"
#include "tileType.h"
#include "Maps.h"
#include "sprites.h"
#include "player.h"
#include "camera.h"

Arduboy2 arduboy;
Game game;
Game::GameState gameState;

void Game::setup()
{
    arduboy.begin();
}

void Game::loop()
{
    if(!arduboy.nextFrame())
        return;

    arduboy.pollButtons();

    arduboy.clear();
    update();
    arduboy.display();
}

void Game::update()
{
    switch(gameState)
    {
        case GameState::Title:
        {
            if (arduboy.justPressed(A_BUTTON))
                gameState = GameState::Game;
            break;
        }

        case GameState::Game:
        {
            updateGame();
            drawMap();
            player.updatePlayer();
            camera.updateCamera();
            player.drawPlayer();
            break;
        }

        case GameState::Gameover:
        {
            break;
        }
    }
}

void Game::updateGame()
{

}

void Game::drawMap()
{
    // Make a reference to the current map
    auto & map = this->getCurrentMap();

    // Loop through all tiles
    for(uint8_t tileY = 0; tileY < map.getHeight(); ++tileY)
    {
        int16_t drawY = ((tileY * tileHeight) - camera.y);

        // If the tile is off screen
        if ((drawY < -tileHeight) || (drawY > arduboy.height()))
            // Skip it
            continue;

        for(uint8_t tileX = 0; tileX < map.getWidth(); ++tileX)
        {
            int16_t drawX = ((tileX * tileWidth) - camera.x);

            // If the tile is off screen
            if((drawX < -tileWidth) || (drawX > arduboy.width()))
			
                continue;

            // Get the tile
            TileType tileType = map.getTile(tileX, tileY);

            // Get the corresponding index
            uint8_t tileIndex = getTileIndex(tileType);

            // Draw the tile
            Sprites::drawSelfMasked(drawX, drawY, mapTiles, tileIndex);
        }
    }
}
