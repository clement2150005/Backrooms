/*==================================================================//
// 		 ____			  _								  			//
// 		|  _ \		  	 | |								 		//
// 		| |_) | __ _  ___| | ___ __ ___   ___  _ __ ___  ___ 		//
// 		|  _ < / _` |/ __| |/ | '__/ _ \ / _ \| '_ ` _ \/ __|		//
// 		| |_) | (_| | (__|   <| | | (_) | (_) | | | | | \__ \		//
// 		|____/ \__,_|\___|_|\_|_|  \___/ \___/|_| |_| |_|___/		//
//																	//
//			Author:   Clement Colin									//
//			Created:  February 6, 2025								//
//==================================================================*/

#include <backrooms.h>

void	debug_statements(t_game *game)
{
	if (SHOW_FPS)
		printf("FPS = %f\n", FPS);
	if (SHOW_DIRECTION)
		printf("dir x = %f dir y = %f\n", PLAYER_DIR_X, PLAYER_DIR_Y);
	if (SHOW_POSITION)
		printf("pos x = %f pos y = %f\n", PLAYER_X, PLAYER_Y);
	if (SHOW_CAM_PLANE)
		printf("camera plane x = %f camera plane y = %f\n", PLAYER_CAM_X, PLAYER_CAM_Y);
}

void	print_entities(t_game *game)
{
	int	i;
	int	e;

	if (!PRINT_ENTITIES)
		return ;
	if (!game)
	{
		printf("Game structure is NULL.\n");
		return ;
	}
	printf("==== Entity Data ====\n");
	i = 0;
	while (i < NUMBER_OF_MAPS)
	{
		printf("Map %d:\n", i + 1);
		if (game->player && game->player[i])
			printf("Player Start: X = %f, Y = %f, Dir = (%.1f, %.1f)\n",
				game->player[i]->x, game->player[i]->y,
				game->player[i]->dir.x, game->player[i]->dir.y);
		else
			printf("  No Player Found\n");
		if (game->enemy && game->enemy[i])
		{
			e = 0;
			while (game->enemy[i][e])
			{
				printf("Enemy %d: X = %f, Y = %f, Dir = (%.1f, %.1f)\n",
					e + 1, game->enemy[i][e]->x, game->enemy[i][e]->y,
					game->enemy[i][e]->dir.x, game->enemy[i][e]->dir.y);
				e++;
			}
		}
		else
			printf("No Enemies Found\n");
		printf("------------------------\n");
		i++;
	}
}

void	print_all_maps(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	if (!PRINT_MAPS)
		return ;
	if (!game->maps)
	{
		printf("No maps loaded.\n");
		return ;
	}
	while (game->maps[i])
	{
		printf("Map %d:\n", i + 1);
		j = 0;
		while (game->maps[i][j])
		{
			printf("%s\n", game->maps[i][j]);
			j++;
		}
		printf("------------------------\n");
		i++;
	}
}
