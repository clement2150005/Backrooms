/*==================================================================//
// 		 ____			  _								  			//
// 		|  _ \		  	 | |								 		//
// 		| |_) | __ _  ___| | ___ __ ___   ___  _ __ ___  ___ 		//
// 		|  _ < / _` |/ __| |/ | '__/ _ \ / _ \| '_ ` _ \/ __|		//
// 		| |_) | (_| | (__|   <| | | (_) | (_) | | | | | \__ \		//
// 		|____/ \__,_|\___|_|\_|_|  \___/ \___/|_| |_| |_|___/		//
//																	//
//			Author:   Clement Colin									//
//			Created:  February 7, 2025								//
//==================================================================*/

#include <backrooms.h>

void	move_player(t_game *game, int key)
{
	if (key == W)
	{
		PLAYER_X = PLAYER_X + (PLAYER_DIR_X * (PLAYER_SPEED) * (1.0 / FPS));
		PLAYER_Y = PLAYER_Y + (PLAYER_DIR_Y * (PLAYER_SPEED) * (1.0 / FPS));
	}
	if (key == S)
	{
		PLAYER_X = PLAYER_X - (PLAYER_DIR_X * (PLAYER_SPEED) * (1.0 / FPS));
		PLAYER_Y = PLAYER_Y - (PLAYER_DIR_Y * (PLAYER_SPEED) * (1.0 / FPS));
	}
}

void	rotate_player(t_game *game, int key)
{
	float	old_dir_x;
	float	length;

	old_dir_x = PLAYER_DIR_X;
	length = sqrtf(PLAYER_DIR_X * PLAYER_DIR_X + PLAYER_DIR_Y * PLAYER_DIR_Y);
	if (key == D)
	{
		PLAYER_DIR_X = PLAYER_DIR_X - PLAYER_DIR_Y * PLAYER_ROTATION_SPEED;
		PLAYER_DIR_Y = PLAYER_DIR_Y + old_dir_x * PLAYER_ROTATION_SPEED;
	}
	if (key == A)
	{
		PLAYER_DIR_X = PLAYER_DIR_X + PLAYER_DIR_Y * PLAYER_ROTATION_SPEED;
		PLAYER_DIR_Y = PLAYER_DIR_Y - old_dir_x * PLAYER_ROTATION_SPEED;
	}
	if (length > 0)
	{
		PLAYER_DIR_X /= length;
		PLAYER_DIR_Y /= length;
	}
}

void	update_player(t_game *game)
{
	if (KEYS[W])
		move_player(game, W);
	if (KEYS[S])
		move_player(game, S);
	if (KEYS[A])
		rotate_player(game, A);
	if (KEYS[D])
		rotate_player(game, D);
}

void	update_entities(t_game *game)
{
	update_player(game);
}
