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

void	handle_events(t_game *game, int *running)
{
	while (SDL_PollEvent(&EVENT))
	{
		if (EVENT.type == SDL_QUIT)
		{
			*running = 0;
		}
		if (EVENT.type == SDL_WINDOWEVENT && EVENT.window.event == SDL_WINDOWEVENT_RESIZED)
		{
			WIND_WIDTH = EVENT.window.data1;
			WIND_HEIGHT = EVENT.window.data2;
			if (WIND_WIDTH / WIND_HEIGHT != 1,7777)
			{
				WIND_HEIGHT = WIND_WIDTH * 9 / 16;
				SDL_SetWindowSize(WINDOW, WIND_WIDTH, WIND_HEIGHT);
			}
		}
	}
}
