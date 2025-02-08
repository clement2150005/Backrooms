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
	cleanup(game);
}

void	manage_fps(t_game *game)
{
	static Uint32	last_time = 0;
	Uint32			start_time;
	Uint32			end_time;
	float			elapsed_time;
	float			frame_time_goal;
	float			wait_time;
	float			total_frame_time;

	start_time = SDL_GetTicks();
	if (last_time == 0)
		last_time = start_time;
	elapsed_time = (start_time - last_time) / 1000.0f;
	if (elapsed_time > 0.0001f)
		game->fps = 1.0f / elapsed_time;
	else
		game->fps = (float)FPS_CAP;
	frame_time_goal = 1.0f / (float)FPS_CAP;
	wait_time = frame_time_goal - elapsed_time;
	if (wait_time > 0)
		SDL_Delay((Uint32)(wait_time * 1000));
	end_time = SDL_GetTicks();
	total_frame_time = (end_time - last_time) / 1000.0f;
	game->fps = 1.0f / total_frame_time;
	printf("TRUE FPS: %.2f\n", game->fps);
	printf("goal %f frame %f wait %f\n",
		frame_time_goal, total_frame_time, wait_time);
	fflush(stdout);
	last_time = end_time;
}

void	game_loop(t_game *game)
{
	int		running;
	void	(*chapter[])(t_game *game, int *running) = {chapter_1, chapter_2, chapter_3, chapter_4, chapter_5};

	running = TRUE;
	LEVEL = 0;
	while (running)
	{
		manage_fps(game);
		chapter[LEVEL](game, &running);
		handle_events(game, &running);
		update_entities(game);
		render_next_frame(game);
	}
}

int	main(void)
{
	t_game	*game;

	game = game_init();
	game_loop(game);
	quit_game(game);
	return (0);
}

/*
TO DO
- Copy maps into array
- Print minimap
- Handle collisions
- Raycast
*/
