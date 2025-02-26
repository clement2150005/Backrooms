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

void	get_P_cores(t_game *game)
{
	int pcores = 0;
	size_t size = sizeof(pcores);
	if (sysctlbyname("hw.perflevel0.logicalcpu", &pcores, &size, NULL, 0) == 0)
		game->P_cores = pcores;
	else
		game->P_cores = 0;
}

void	init_game_variables(t_game *game)
{
	game->fps = 0;
	game->level = 0;
	game->maps = NULL;
	game->player = NULL;
	game->enemy = NULL;
	game->speed = DEFAULT_SPEED;
	game->moving = 0;
	game->window = NULL;
	game->renderer = NULL;
	game->wind_width = 0;
	game->wind_height = 0;
	game->z_buffer = NULL;
	game->vector_grid = NULL;
	game->screen = NULL;
	game->P_cores = 0;
	game->event = (SDL_Event){0};
	game->input = (t_input){0};
	game->textures = (t_textures){0};
	game->sounds = (t_sounds){0};
}


static t_game	*game_struct_init()
{
	t_game *game;
	game = malloc(sizeof(t_game));
	if (!game)
	{
		fprintf(stderr, "ERROR: memory allocation failed in game_init");
		exit(EXIT_FAILURE);
	}
	init_game_variables(game);
	init_maps(game);
	print_all_maps(game);
	init_vector_grid(game);
	init_entities(game);
	print_entities(game);
	get_P_cores(game);
	game->z_buffer = calloc(WIND_HEIGHT * WIND_WIDTH, sizeof(float));
	if (!game->z_buffer)
		cleanup(game);
	game->screen = calloc(WIND_HEIGHT * WIND_WIDTH, sizeof(float));
	if (!game->z_buffer)
		cleanup(game);
	KEYS = malloc(sizeof(int) * HOW_MANY_KEYS);
	if (!KEYS)
	{
		fprintf(stderr, "ERROR: memory allocation failed in game_struct_init");
		cleanup(game);
	}
}

static void	graphics_init(t_game *game)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("SDL_Init Error: %s\n", SDL_GetError());
		cleanup(game);
	}
	WINDOW = SDL_CreateWindow("Backrooms", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_FULLSCREEN_DESKTOP);
	if (!WINDOW)
	{
		printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
		cleanup(game);
	}
	if (VSYNC)
		RENDERER = SDL_CreateRenderer(WINDOW, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	else
		RENDERER = SDL_CreateRenderer(WINDOW, -1, SDL_RENDERER_ACCELERATED);
	if (!RENDERER)
	{
		printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
		cleanup(game);
	}
	SDL_GetWindowSize(WINDOW, &WIND_WIDTH, &WIND_HEIGHT);
}

void	controller_init(t_game *game)
{
	SDL_GameController	*controller;

	if (SDL_Init(SDL_INIT_GAMECONTROLLER) < 0)
	{
		printf("SDL could not initialize! Error: %s\n", SDL_GetError());
		cleanup(game);
	}
	controller = NULL;
	if (SDL_NumJoysticks() > 0 && SDL_IsGameController(0))
	{
		controller = SDL_GameControllerOpen(0);
		if (!controller)
		{
			printf("Failed to open controller: %s\n", SDL_GetError());
		}
		else
		{
			printf("Controller connected: %s\n", SDL_GameControllerName(controller));
		}
	}
	else
	{
		printf("No compatible controller found.\n");
	}
}

void	load_texture(t_game *game, const char *path, t_texture *dest)
{
	SDL_Surface	*surface;

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
	{
		printf("IMG_Init Error: %s\n", IMG_GetError());
		cleanup(game);
	}
	surface = IMG_Load(path);
	if (!surface)
	{
		printf("IMG_Load Error: %s\n", IMG_GetError());
		cleanup(game);
	}
	dest->texture = SDL_CreateTextureFromSurface(game->renderer, surface);
	if (!dest->texture)
	{
		printf("SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
		SDL_FreeSurface(surface);
		cleanup(game);
	}
	dest->width = surface->w;
	dest->height = surface->h;
	dest->pixels = (Uint32 *)malloc(dest->width * dest->height * sizeof(Uint32));
	if (!dest->pixels)
	{
		printf("Memory allocation failed for texture pixels\n");
		SDL_FreeSurface(surface);
		cleanup(game);
	}
	memcpy(dest->pixels, surface->pixels, dest->width * dest->height * sizeof(Uint32));
	SDL_FreeSurface(surface);
	SDL_QueryTexture(dest->texture, NULL, NULL, &dest->width, &dest->height);
}

void	load_textures(t_game *game)
{
	game->textures.screen_texture = SDL_CreateTexture
		(
			game->renderer,
			SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING,
			WIND_WIDTH,
			WIND_HEIGHT
			);
	if (!game->textures.screen_texture)
	{
		printf("SDL_CreateTexture Error: %s\n", SDL_GetError());
		cleanup(game);
	}
	load_texture(game, "./assets/textures/png/wall.png", &game->textures.wall);
	load_texture(game, "./assets/textures/png/wall_dark.png", &game->textures.wall_dark);
	load_texture(game, "./assets/textures/png/ceiling.png", &game->textures.ceiling);
	load_texture(game, "./assets/textures/png/ceiling_dark.png", &game->textures.ceiling_dark);
	load_texture(game, "./assets/textures/png/ceiling_darker.png", &game->textures.ceiling_darker);
	load_texture(game, "./assets/textures/png/floor.png", &game->textures.floor);
	load_texture(game, "./assets/textures/png/floor_light.png", &game->textures.floor_light);
	load_texture(game, "./assets/textures/png/floor_lighter.png", &game->textures.floor_lighter);
}

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

t_game	*game_init(void)
{
	t_game	*game;

	game = game_struct_init();
	controller_init(game);
	graphics_init(game);
	sound_init(game);
	load_textures(game);
	SDL_SetHint(SDL_HINT_MOUSE_RELATIVE_MODE_WARP, "0");
	SDL_SetRelativeMouseMode(SDL_TRUE);
	return (game);
}
