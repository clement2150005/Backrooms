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

void	controller_keydown(t_game *game, SDL_GameControllerButton button)
{
	if (button == SDL_CONTROLLER_BUTTON_A)
		JUMP = JUMP_UP;
	else if (button == SDL_CONTROLLER_BUTTON_B)
		KEYS[C] = TRUE;
	else if (SDL_CONTROLLER_BUTTON_LEFTSTICK)
		PLAYER_SPEED = (PLAYER_SPEED == DEFAULT_SPEED) ? DEFAULT_SPEED + 2 : DEFAULT_SPEED;
}

void	controller_keyup(t_game *game, SDL_GameControllerButton button)
{
	if (button == SDL_CONTROLLER_BUTTON_B)
		KEYS[C] = FALSE;
}
