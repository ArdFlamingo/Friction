#include "player.h"
#include "game.h"
#include "sprites.h"
#include "camera.h"
#include "tileType.h"
#include "Maps.h"

Player player;
Camera camera;

void Player::updatePlayer()
{
    playerInput();

    game.arduboy.setCursor(0, 0);
    game.arduboy.println(x);
	game.arduboy.println(y);

    auto & map = game.getCurrentMap();

    yVelocity += Physics::gravity;
    xVelocity *= Physics::friction;

	auto newX = (this->x + this->xVelocity);
    auto newY = (this->y + this->yVelocity);

    const int16_t tileX = ((newX + halfTileWidth) / tileWidth);
    const int16_t tileY = ((newY + halfTileHeight) / tileHeight);

    const int16_t rightX = (newX + this->size);

    const int16_t rightTileX = (rightX / tileWidth);

    const TileType rightTile = map.getTile(rightTileX, tileY);

    if (isSolid(rightTile))
    {
        newX = ((rightTileX * tileWidth) - this->size);
		xVelocity = 0;
    }
    
    const int16_t leftX = (newX);
    
    const int16_t leftTileX = (leftX / tileWidth);

    const TileType leftTile = map.getTile(leftTileX, tileY);

    if (isSolid(leftTile))
    {
        newX = ((leftTileX + 1) * tileWidth);
		xVelocity = 0;
    }

    const int16_t bottomY = (newY + this->size);

    const int16_t bottomTileY = (bottomY / tileHeight);

    const TileType bottomTile = map.getTile(tileX, bottomTileY);

    if (isSolid(bottomTile))
    {	
		newY = ((bottomTileY * tileHeight) - this->size);
		yVelocity = 0;

		grounded = true;
    }

	else
	{
		if (game.arduboy.everyXFrames(15))
			grounded = false;
	}

    const int16_t topY = (newY - 1);

    const int16_t topTileY = (topY / tileHeight);

    const TileType topTile = map.getTile(tileX, topTileY);

    if (isSolid(topTile))
    {
        newY = ((topTileY + 1) * tileHeight);
		yVelocity = -0.25;
    }

    this->x = ((newX > 0) ? newX : 0);
    this->y = newY;
}

void Camera::updateCamera()
{
    if (x <= 0)
        isLeft = true;

    // Make a reference to the current map
    auto & map = game.getCurrentMap();

    const auto fullMapWidth = (map.getWidth() * tileWidth);

	const uint8_t centerPoint = ((Arduboy2::width() / 2) - player.getSize());

    if (x >= (fullMapWidth - Arduboy2::width()))
        isRight = true;

    if (isLeft)
    {
        if (player.x >= centerPoint)
            isLeft = false;
    }

    if (isRight)
    {
        if (player.x <= (fullMapWidth - centerPoint))
            isRight = false;
    }

    if (!isLeft && !isRight)
    {
        x = (player.x - (Arduboy2::width() / 2));
    }

	if (player.y < 0)
	{
		y = player.y;
	}
	else
	{
		y = 0;
	}	
}

void Player::playerInput()
{   
    if (game.arduboy.pressed(RIGHT_BUTTON))
    {
        xVelocity += Physics::speed;

        isPlayerLeft = false;
    }

    if (game.arduboy.pressed(LEFT_BUTTON))
    {
        xVelocity -= Physics::speed;
    
        isPlayerLeft = true;
    }

    if (game.arduboy.pressed(A_BUTTON))
    {    
		if (grounded)
		{
			yVelocity = 0;
			yVelocity -= Physics::thrust;
		}
    }
}

void Player::drawPlayer()
{
	if (!blink)
	{
		game.arduboy.everyXFrames(10);
		{
			//blink = true;
		}
		
		Sprites::drawOverwrite((x - camera.x), (y  - camera.y), playerSprite, isPlayerLeft);
	}

	else
	{
		game.arduboy.everyXFrames(5);
		{
			blink = false;
		}

		Sprites::drawOverwrite((x - camera.x), (y  - camera.y), playerSprite, 2);
	}
}
