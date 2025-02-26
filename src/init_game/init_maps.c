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

void	init_maps(t_game *game)
{
	char	*path;
	int		i = 1;

	MAPS = malloc(sizeof(char **) * (NUMBER_OF_MAPS + 1));
	if (!MAPS)
	{
		fprintf(stderr, "ERROR: memory allocation failed in init_maps");
		exit(EXIT_FAILURE);
	}
	while (i <= NUMBER_OF_MAPS)
	{
		path = get_path(i);
		MAPS[i - 1] = get_map(path);
		if (!MAPS[i - 1])
			cleanup(game);
		free(path);
		if (!MAPS[i - 1])
		{
			free(MAPS);
			MAPS = NULL;
			return ;
		}
		i++;
	}
	MAPS[NUMBER_OF_MAPS] = NULL;
}

