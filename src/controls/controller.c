/*==================================================================//
// 		 ____			  _								  			//
// 		|  _ \		  	 | |								 		//
// 		| |_) | __ _  ___| | ___ __ ___   ___  _ __ ___  ___ 		//
// 		|  _ < / _` |/ __| |/ | '__/ _ \ / _ \| '_ ` _ \/ __|		//
// 		| |_) | (_| | (__|   <| | | (_) | (_) | | | | | \__ \		//
// 		|____/ \__,_|\___|_|\_|_|  \___/ \___/|_| |_| |_|___/		//
//																	//
//			Author:   Clement Colin									//
//			Created:  February 19, 2025								//
//==================================================================*/

#include <backrooms.h>

void	left_stick(t_game *game)
{
	static int	last_time;
	int			new_time;
	int			ellapsed;

	new_time = SDL_GetTicks();
	ellapsed = new_time - last_time;
	if (fabs(JOYSTICK_Y) < 0.1 && fabs(JOYSTICK_X) < 0.1)
	{
		if (ellapsed > 100)
		{
			if (!KEYS[SHIFT])
				PLAYER_SPEED = DEFAULT_SPEED;
		}
	}
	else
		last_time = new_time;
}

void	manage_controller(t_game *game)
{
	left_stick(game);
}
