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

void	sound_init(t_game *game)
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		fprintf(stderr, "SDL_mixer Error: %s\n", Mix_GetError());
		cleanup(game);
	}
	SOUNDS.ambient = Mix_LoadMUS("./assets/sounds/neon.wav");
	if (!SOUNDS.ambient)
	{
		fprintf(stderr, "Failed to load ambient sound: %s\n", Mix_GetError());
		cleanup(game);
	}
	SOUNDS.running = Mix_LoadWAV("./assets/sounds/running.wav");
	if (!SOUNDS.running)
	{
		fprintf(stderr, "Failed to load sound effect: %s\n", Mix_GetError());
		cleanup(game);
	}
	SOUNDS.walking = Mix_LoadWAV("./assets/sounds/walking.wav");
	if (!SOUNDS.walking)
	{
		fprintf(stderr, "Failed to load sound effect: %s\n", Mix_GetError());
		cleanup(game);
	}
	Mix_VolumeMusic(64);
	Mix_Volume(1, 64);
	Mix_Volume(2, 64);
}
