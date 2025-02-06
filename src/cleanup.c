/*==================================================================//
// 		 ____			  _								  			//
// 		|  _ \		  	 | |								 		//
// 		| |_) | __ _  ___| | ___ __ ___   ___  _ __ ___  ___ 		//
// 		|  _ < / _` |/ __| |/ | '__/ _ \ / _ \| '_ ` _ \/ __|		//
// 		| |_) | (_| | (__|   <| | | (_) | (_) | | | | | \__ \		//
// 		|____/ \__,_|\___|_|\_|_|  \___/ \___/|_| |_| |_|___/		//
//																	//
//			Author:   Clement Colin									//
//			Created:  February 5, 2025								//
//==================================================================*/

#include <backrooms.h>

void	free_entities(t_game *game)
{
	int	i;
	int	e;

	if (!game)
		return;
	if (game->player_start)
	{
		i = 0;
		while (i < NUMBER_OF_MAPS)
			free(game->player_start[i++]);
		free(game->player_start);
		game->player_start = NULL;
	}
	if (game->enemy_start)
	{
		i = 0;
		while (i < NUMBER_OF_MAPS)
		{
			if (game->enemy_start[i])
			{
				e = 0;
				while (game->enemy_start[i][e])
					free(game->enemy_start[i][e++]);
				free(game->enemy_start[i]);
			}
			i++;
		}
		free(game->enemy_start);
		game->enemy_start = NULL;
	}
}

void free_all(char **array) 
{
	if (!array) return;

	int i = 0;
	while (array[i]) {
		free(array[i]);
		i++;
	}
	free(array);
}

void free_all_maps(t_game *game)
{
	if (!game->maps)
		return;

	int i = 0;
	while (game->maps[i])
	{
		free_all(game->maps[i]);
		i++;
	}

	free(game->maps);
	game->maps = NULL;
}

void	cleanup(t_game *game)
{
	if (game->frames)
		free(game->frames);
	free_all_maps(game);
	free_entities(game);
	free(game);
}
