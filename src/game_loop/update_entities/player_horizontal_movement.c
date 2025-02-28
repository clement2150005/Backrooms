/*==================================================================//
// 		 ____			  _								  			//
// 		|  _ \		  	 | |								 		//
// 		| |_) | __ _  ___| | ___ __ ___   ___  _ __ ___  ___ 		//
// 		|  _ < / _` |/ __| |/ | '__/ _ \ / _ \| '_ ` _ \/ __|		//
// 		| |_) | (_| | (__|   <| | | (_) | (_) | | | | | \__ \		//
// 		|____/ \__,_|\___|_|\_|_|  \___/ \___/|_| |_| |_|___/		//
//																	//
//			Author:   Clement Colin									//
//			Created:  February 26, 2025								//
//==================================================================*/

#include <backrooms.h>

void	move_player(t_game *game, int key)
{
	float	x;
	float	y;

	if (key == W)
	{
		x = PLAYER_X + (PLAYER_DIR_X * PLAYER_SPEED * FRAME_TIME);
		y = PLAYER_Y + (PLAYER_DIR_Y * PLAYER_SPEED * FRAME_TIME);
	}
	if (key == S)
	{
		x = PLAYER_X - (PLAYER_DIR_X * PLAYER_SPEED * FRAME_TIME);
		y = PLAYER_Y - (PLAYER_DIR_Y * PLAYER_SPEED * FRAME_TIME);
	}
	if (key == A)
	{
		x = PLAYER_X + (PLAYER_DIR_Y * (PLAYER_SPEED * 0.6) * FRAME_TIME);
		y = PLAYER_Y - (PLAYER_DIR_X * (PLAYER_SPEED * 0.6) * FRAME_TIME);
	}
	if (key == D)
	{
		x = PLAYER_X - (PLAYER_DIR_Y * (PLAYER_SPEED * 0.6) * FRAME_TIME);
		y = PLAYER_Y + (PLAYER_DIR_X * (PLAYER_SPEED * 0.6) * FRAME_TIME);
	}
	collisions(game, x, y);
	if (PLAYER_SPEED == DEFAULT_SPEED)
		MOVING = WALKING;
	else
		MOVING = RUNNING;
}


void	move_player_joystick(t_game *game, float x, float y)
{
	float	move_x = PLAYER_X;
	float	move_y = PLAYER_Y;

	if (fabs(x) > 0.1)
	{
		move_x -= PLAYER_DIR_Y * (PLAYER_SPEED * 0.6) * (x * FRAME_TIME);
		move_y += PLAYER_DIR_X * (PLAYER_SPEED * 0.6) * (x * FRAME_TIME);
	}
	if (fabs(y) > 0.1)
	{
		move_x += PLAYER_DIR_X * PLAYER_SPEED * (y * FRAME_TIME);
		move_y += PLAYER_DIR_Y * PLAYER_SPEED * (y * FRAME_TIME);
	}
	collisions(game, move_x, move_y);
	if (PLAYER_SPEED == DEFAULT_SPEED)
		MOVING = WALKING;
	else
		MOVING = RUNNING;
}
