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

static void	keydown(t_game *game, SDL_KeyCode code)
{
	if (code == SDLK_w && !KEYS[S])
		KEYS[W] = TRUE;
	if (code == SDLK_a && !KEYS[D])
		KEYS[A] = TRUE;
	if (code == SDLK_s && !KEYS[W])
		KEYS[S] = TRUE;
	if (code == SDLK_d && !KEYS[A])
		KEYS[D] = TRUE;
}

static void	keyup(t_game *game, SDL_KeyCode code)
{
	if (code == SDLK_w)
		KEYS[W] = FALSE;
	if (code == SDLK_a)
		KEYS[A] = FALSE;
	if (code == SDLK_s)
		KEYS[S] = FALSE;
	if (code == SDLK_d)
		KEYS[D] = FALSE;
}

void	handle_events(t_game *game, int *running)
{
	while (SDL_PollEvent(&EVENT))
	{
		if (EVENT.type == SDL_QUIT)
		{
			*running = 0;
		}
		if (EVENT.type == SDL_KEYDOWN && EVENT.key.keysym.sym == SDLK_ESCAPE)
		{
			*running = 0;
		}
		if (EVENT.type == SDL_WINDOWEVENT && EVENT.window.event == SDL_WINDOWEVENT_RESIZED)
		{
			WIND_WIDTH = EVENT.window.data1;
			WIND_HEIGHT = EVENT.window.data2;
			if (WIND_WIDTH / WIND_HEIGHT != 1.7777)
			{
				WIND_HEIGHT = WIND_WIDTH * 9 / 16;
				SDL_SetWindowSize(WINDOW, WIND_WIDTH, WIND_HEIGHT);
			}
		}
		if (EVENT.type == SDL_KEYDOWN)
			keydown(game, EVENT.key.keysym.sym);
		if (EVENT.type == SDL_KEYUP)
			keyup(game, EVENT.key.keysym.sym);
	}
}
