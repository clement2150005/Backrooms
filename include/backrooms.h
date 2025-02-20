#ifndef BACKROOMS_H
# define BACKROOMS_H

# include <SDL2/SDL_image.h>
# include <SDL2/SDL_mixer.h>
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>
# include <fcntl.h>

#define MAP_HEIGHT 23
#define MAP_WIDTH 50


//==============================MACROS
// SETTINGS
# define FOV			53
# define FPS_CAP		60
# define DEFAULT_SPEED	2
# define MOUSE_SENSIT	0.01
# define JOY_SENSIT		2
# define PIXEL_BLOCK	1
# define VSYNC			TRUE

// DEBUG
# define START_LEVEL	0
# define PRINT_ENTITIES FALSE
# define PRINT_MAPS 	FALSE
# define SHOW_MINIMAP 	FALSE
# define SHOW_PATH_FIND FALSE
# define SHOW_FPS		FALSE
# define SHOW_DIRECTION	FALSE
# define SHOW_POSITION	FALSE
# define SHOW_CAM_PLANE	FALSE
# define MINIMAP_BLOCK	25

// MAP CHARACTERS
# define WALL			'#'
// Sticking out of the floor
# define WALL_0			'0'
# define WALL_1			'1'
# define WALL_2			'2'
# define WALL_3			'3'
# define WALL_4			'4'
// Sticking out of the ceiling
# define WALL_5			'5'
# define WALL_6			'6'
# define WALL_7			'7'
# define WALL_8			'8'
# define WALL_9			'9'
# define VOID			'.'
# define EMPTY			' '
# define P_NORTH		'N'
# define P_SOUTH		'S'
# define P_EAST			'E'
# define P_WEST			'W'
# define E_NORTH		'n'
# define E_SOUTH		's'
# define E_EAST			'e'
# define E_WEST			'w'
# define DOOR_CLOSED	'D'
# define DOOR_OPENED	'U'
# define DOOR_CLOSING	'd'
# define DOOR_OPENING	'u'
# define TRIGGER		'T'

// KEYS
# define W				0
# define A				1
# define S				2
# define D				3
# define SHIFT			4
# define C				5
# define HOW_MANY_KEYS	6

// PLAYER MOVEMENT

# define STILL			0
# define RUNNING		1
# define WALKING		2

// OTHERS
# define TRUE			1
# define FALSE			0
# define NUMBER_OF_MAPS	5
# define BUFFER_SIZE	64
# define NORTH			0x0080A0 // Blue
# define SOUTH			0x228B22 // Green
# define EAST			0x800080 // Purple
# define WEST			0xA52A2A // Red

//==============================STRUCTS
typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_float_xy
{
	float				x;
	float				y;
}						t_float_xy;

typedef struct s_dda_result
{
	t_point				*cells;
	t_float_xy			dir;
	int					count;
}						t_dda_result;

typedef struct s_entity
{
	float				x;
	float				y;
	t_float_xy			dir;
	t_float_xy			cam;
}						t_entity;

typedef struct s_frames
{
	int					frame_time;
	Uint32				frame_start;
}						t_frames;

typedef struct s_sounds
{
	Mix_Music			*ambient;
	Mix_Chunk			*running;
	Mix_Chunk			*walking;
}						t_sounds;

typedef struct s_mini_ray
{
	int					detetcted;
	int					x;
	int					side;
	float				pos_x;
	float				pos_y;
	float				ray_dir_x;
	float				ray_dir_y;
	float				perp_wall_dist;
}						t_mini_ray;

typedef struct s_mini_ray_node
{
	t_mini_ray			ray;
	struct s_mini_ray_node *next;
}						t_mini_ray_node;


typedef struct s_raycaster
{
	int					x;
	int					side;
	float				pos_x;
	float				pos_y;
	int					map_x;
	int					map_y;
	float				cam_x;
	int					step_x;
	float				offset;
	int					step_y;
	int					wall_dir;
	float				ray_dir_x;
	float				ray_dir_y;
	float				wall_hit_y;
	float				wall_hit_x;
	float				side_dist_x;
	float				side_dist_y;
	float				delta_dist_x;
	float				delta_dist_y;
	float				perp_wall_dist;
	t_mini_ray_node		*mini_ray;
}						t_raycaster;


typedef struct s_input
{
	int					*keys;
	int					mouse_x_rel;
	int					mouse_y_rel;
	float				joystick_velocity_x;
	float				joystick_velocity_y;
	float				joystick_rotation_x;
	float				joystick_rotation_y;
}						t_input;

typedef struct s_texture
{
	SDL_Texture			*texture;
	Uint32				*pixels;
	int					width;
	int					height;
}						t_texture;

typedef struct s_textures
{
	SDL_Texture			*screen_texture;
	t_texture			wall;
	t_texture			ceiling;
	t_texture			floor;
}						t_textures;

typedef struct s_game
{
	float				fps;
	SDL_Event			event;
	t_input				input;
	int					level;
	SDL_Window			*window;
	char				***maps;
	t_entity			**player;
	t_entity			***enemy;
	int					speed;
	int					moving;
	t_textures			textures;
	SDL_Renderer		*renderer;
	int					wind_width;
	int					wind_height;
	t_float_xy			***vector_grid;
	t_sounds			sounds;
	int					camera_shift;
}						t_game;

# define FPS			game->fps
# define MAPS			game->maps
# define LEVEL			game->level
# define CAM_SHIFT		game->camera_shift
# define EVENT			game->event
# define ENEMY			game->ENEMY
# define MOVING			game->moving
# define SOUNDS			game->sounds
# define PLAYER			game->player
# define WINDOW			game->window
# define RENDERER		game->renderer
# define KEYS			game->input.keys
# define WIND_WIDTH		game->wind_width
# define WIND_HEIGHT	game->wind_height
# define PLAYER_SPEED	game->speed
# define VECTOR_GRID	game->vector_grid
# define MOUSE_X		game->input.mouse_x_rel
# define MOUSE_Y		game->input.mouse_y_rel
# define PLAYER_X		game->player[(LEVEL)]->x
# define PLAYER_Y		game->player[(LEVEL)]->y
# define PLAYER_DIR_X	game->player[(LEVEL)]->dir.x
# define PLAYER_DIR_Y	game->player[(LEVEL)]->dir.y
# define PLAYER_CAM_X	game->player[(LEVEL)]->cam.x
# define PLAYER_CAM_Y	game->player[(LEVEL)]->cam.y
# define JOYSTICK_ROT_X	game->input.joystick_rotation_x
# define JOYSTICK_ROT_Y	game->input.joystick_rotation_y
# define JOYSTICK_X		game->input.joystick_velocity_x
# define JOYSTICK_Y		game->input.joystick_velocity_y

//==============================FUNCTIONS
char					*get_path(int i);
t_game					*game_init(void);
void					cleanup(t_game *game);
char					**get_map(char *path);
void					free_all(char **array);
char					*get_next_line(int fd);
void					show_fps(t_game *game);
void					quit_game(t_game *game);
void					init_maps(t_game *game);
void					manage_fps(t_game *game);
SDL_Color				int_to_color(Uint32 color);
void					draw_minimap(t_game *game);
void					init_entities(t_game *game);
void					print_all_maps(t_game *game);
void					print_entities(t_game *game);
void					update_entities(t_game *game);
void					init_vector_grid(t_game *game);
void					debug_statements(t_game *game);
void					render_next_frame(t_game *game);
void					update_vector_grid(t_game *game);
void					rotate_player(t_game *game, int x);
void					set_player_cam(t_game *game, int i);
void					manage_controller(t_game *game);
void					set_player_cam(t_game *game, int i);
void					init_raycaster_steps(t_raycaster *r);
void					chapter_1(t_game *game, int *running);
void					chapter_2(t_game *game, int *running);
void					chapter_3(t_game *game, int *running);
void					keydown(t_game *game, SDL_KeyCode code);
void					keyup(t_game *game, SDL_KeyCode code);
void					chapter_4(t_game *game, int *running);
void					chapter_5(t_game *game, int *running);
char					*strjoin(const char *s1, const char *s2);
void					handle_events(t_game *game, int *running);
void					init_raycaster(t_raycaster *r, t_game *game);
void					perform_raycaster_steps(t_raycaster *r, t_game *game);
void					draw_cercle(SDL_Renderer *renderer, int centerX, int centerY, int radius);
void					draw_column(SDL_Renderer *renderer, int x, int yStart, int yEnd, SDL_Color color);

#endif
