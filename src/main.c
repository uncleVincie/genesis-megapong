#include <genesis.h>
#include <resources.h>

/*The edges of the play field*/
const int LEFT_EDGE = 0;
const int RIGHT_EDGE = 320;
const int TOP_EDGE = 0;
const int BOTTOM_EDGE = 224;

Sprite *ball;
Sprite *player;

int ball_pos_x = 100;
int ball_pos_y = 100;
int ball_vel_x = 1;
int ball_vel_y = 1;
int ball_width = 8;
int ball_height = 8;

int player_pos_x = 144;
const int player_pos_y = 200;
int player_vel_x = 0;
const int player_width = 32;
const int player_height = 8;

/*
The callback function for joypad inputs.
pressed = 1 if pressed and 0 if not
changed = 1 if state is different than last frame's state, 0 if not
*/
void myJoyHandler(u16 joy, u16 changed, u16 pressed)
{
    if (joy == JOY_1)
    {
        /*Set player velocity if left or right are pressed;
         *set velocity to 0 if no direction is pressed
         NOTE: need to use bitwise operators here, since enums are hex */
        if (pressed & BUTTON_RIGHT)
        {
            player_vel_x = 3;
        }
        else if (pressed & BUTTON_LEFT)
        {
            player_vel_x = -3;
        }
        else
        {
            if ((changed & BUTTON_RIGHT) | (changed & BUTTON_LEFT))
            {
                player_vel_x = 0;
            }
        }
    }
}

void moveBall()
{
    // check horizontal bounds
    if (ball_pos_x < LEFT_EDGE)
    {
        ball_pos_x = LEFT_EDGE;
        ball_vel_x = -ball_vel_x;
    }
    else if (ball_pos_x + ball_width > RIGHT_EDGE)
    {
        ball_pos_x = RIGHT_EDGE - ball_width;
        ball_vel_x = -ball_vel_x;
    }

    // check vertical bounds
    if (ball_pos_y < TOP_EDGE)
    {
        ball_pos_y = TOP_EDGE;
        ball_vel_y = -ball_vel_y;
    }
    else if (ball_pos_y + ball_height > BOTTOM_EDGE)
    {
        ball_pos_y = BOTTOM_EDGE - ball_height;
        ball_vel_y = -ball_vel_y;
    }

    // calculate new ball posish
    ball_pos_x += ball_vel_x;
    ball_pos_y += ball_vel_y;

    // update sprite engine with new posish
    SPR_setPosition(ball, ball_pos_x, ball_pos_y);
}

void positionPlayer()
{
    /*Add the player's velocity to its position*/
    player_pos_x += player_vel_x;

    /*Keep the player within the bounds of the screen*/
    if (player_pos_x < LEFT_EDGE)
        player_pos_x = LEFT_EDGE;
    if (player_pos_x + player_width > RIGHT_EDGE)
        player_pos_x = RIGHT_EDGE - player_width;

    /*Let the Sprite engine position the sprite*/
    SPR_setPosition(player, player_pos_x, player_pos_y);
}

int main()
{
    // Input
    JOY_init();
    JOY_setEventHandler(&myJoyHandler);

    // Background
    VDP_loadTileSet(bgtile.tileset, 1, DMA);         // load the tileset into position 1 in VRAM, use Direct Memory Access
    PAL_setPalette(PAL1, bgtile.palette->data, DMA); // get pallete data from the asset, load into pallet 1, using DMA
    VDP_fillTileMapRect(BG_B, TILE_ATTR_FULL(PAL1, 0, FALSE, FALSE, 1), 0, 0, 40, 30);

    // Sprites
    SPR_init();
    ball = SPR_addSprite(&imgball, 100, 100, TILE_ATTR(PAL1, 0, FALSE, FALSE));
    player = SPR_addSprite(&paddle, player_pos_x, player_pos_y, TILE_ATTR(PAL1, 0, FALSE, FALSE));

    while (1)
    {
        moveBall();
        positionPlayer();

        SPR_update();
        SYS_doVBlankProcess();
    }
    return (0);
}
