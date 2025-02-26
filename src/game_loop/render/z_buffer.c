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

void	clear_z_buffer(t_game *game)
{
	for (int i = 0; i < game->wind_width * game->wind_height; i++)
		game->z_buffer[i] = 100;
}

int	check_z_buffer(t_game *game, int index, float z)
{
	if (index < 0 || index >= game->wind_width * game->wind_height)
		return (0);
	return (z < game->z_buffer[index]);
}

void	set_z_buffer(t_game *game, float perp_wall_dist, int index)
{
	if (index >= 0 && index < WIND_WIDTH * WIND_HEIGHT)
		game->z_buffer[index] = perp_wall_dist;
}
