#line 1 "/Users/om/Downloads/ARDUBOY/Friction/player.h"
#pragma once
#include <stdint.h>
#include <Arduboy2.h>

class Player
{
    private:

    struct Physics
    {
        static constexpr float gravity = 0.03;
        static constexpr float friction = 0.915;
		static constexpr float speed = 0.13;
    	static constexpr float thrust = 1.12;
    };

    static constexpr uint8_t size = 8;

    bool isPlayerLeft;
	bool blink;

	bool grounded;

    void playerInput();

    public:

    float x;
    float y;

    float xVelocity;
    float yVelocity;

    void updatePlayer();
    void drawPlayer();

	const uint8_t getSize() const
	{
		return this->size;
	}
};

extern Player player;
