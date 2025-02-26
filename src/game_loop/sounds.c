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

void	sounds(t_game *game)
{
	if (!Mix_PlayingMusic())
	{
		if (Mix_PlayMusic(SOUNDS.ambient, -1) == -1)
		{
			fprintf(stderr, "Failed to play music: %s\n", Mix_GetError());
		}
	}
	if (MOVING == RUNNING)
	{
		if (Mix_Playing(2))
			Mix_HaltChannel(2);
		if (!Mix_Playing(1))
		{
			Mix_PlayChannel(1, SOUNDS.running, 0);
		}
	}
	if (MOVING == WALKING)
	{
		if (Mix_Playing(1))
			Mix_HaltChannel(1);
		if (!Mix_Playing(2))
		{
			Mix_PlayChannel(2, SOUNDS.walking, 0);
		}
	}
	if (MOVING == STILL)
	{
		Mix_HaltChannel(-1);
	}
}
