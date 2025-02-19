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

void	quit_game(t_game *game)
{
	SDL_DestroyWindow(WINDOW);
	SDL_DestroyRenderer(RENDERER);
	SDL_Quit();
	exit(EXIT_SUCCESS);
}

void map_trigger(t_game *game)
{
	if (MAPS[LEVEL][(int)PLAYER_Y][(int)PLAYER_X] == TRIGGER)
	{
		game->player[LEVEL + 1]->x = PLAYER_X;
		game->player[LEVEL + 1]->y = PLAYER_Y;
		game->player[LEVEL + 1]->dir.x = PLAYER_DIR_X;
		game->player[LEVEL + 1]->dir.y = PLAYER_DIR_Y;
		LEVEL++;
	}
}

static void	game_loop(t_game *game)
{
	int		running;
	void	(*chapter[])(t_game *game, int *running) = {chapter_1, chapter_2, chapter_3, chapter_4, chapter_5};

	running = TRUE;
	LEVEL = START_LEVEL;
	while (running)
	{
		chapter[LEVEL](game, &running);
		map_trigger(game);
		handle_events(game, &running);
		manage_controller(game);
		update_entities(game);
		render_next_frame(game);
		debug_statements(game);
		manage_fps(game);
	}
}

int	main(void)
{
	t_game	*game;

	game = game_init();
	game_loop(game);
	cleanup(game);
	return (0);
}
