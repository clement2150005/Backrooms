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

void	keydown(t_game *game, SDL_KeyCode code)
{
	static Uint32	c_timer;

	if (code == SDLK_w)
		KEYS[W] = TRUE;
	if (code == SDLK_a)
		KEYS[A] = TRUE;
	if (code == SDLK_s)
		KEYS[S] = TRUE;
	if (code == SDLK_d)
		KEYS[D] = TRUE;
	if (code == SDLK_c)
		KEYS[C] = TRUE;
	if (code == SDLK_LSHIFT)
	{
		KEYS[SHIFT] = TRUE;
		PLAYER_SPEED = DEFAULT_SPEED + 2;
	}
}

void	keyup(t_game *game, SDL_KeyCode code)
{
	if (code == SDLK_w)
		KEYS[W] = FALSE;
	if (code == SDLK_a)
		KEYS[A] = FALSE;
	if (code == SDLK_s)
		KEYS[S] = FALSE;
	if (code == SDLK_d)
		KEYS[D] = FALSE;
	if (code == SDLK_c)
		KEYS[C] = FALSE;
	if (code == SDLK_LSHIFT)
	{
		KEYS[SHIFT] = FALSE;
		PLAYER_SPEED = DEFAULT_SPEED;
	}
}
