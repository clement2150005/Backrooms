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

//==============================MACROS
// SETTINGS
# define FOV			53
# define FPS_CAP		61
# define PLAYER_SPEED	3
# define MOUSE_SENSIT	0.01
# define JOY_SENSIT		2

// DEBUG
# define PRINT_ENTITIES FALSE
# define PRINT_MAPS 	FALSE
# define SHOW_MINIMAP 	TRUE
# define SHOW_PATH_FIND FALSE
# define SHOW_FPS		TRUE
# define SHOW_DIRECTION	FALSE
# define SHOW_POSITION	FALSE
# define SHOW_CAM_PLANE	FALSE
# define MINIMAP_BLOCK	25

// MAP CHARACTERS
# define WALL			'#'
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

// KEYS
# define W				0
# define A				1
# define S				2
# define D				3
# define HOW_MANY_KEYS	4

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
}						t_raycaster;

typedef struct s_input
{
	int					*keys;
	int					mouse_x_rel;
	float				joystick_velocity_x;
	float				joystick_velocity_y;
	float				joystick_rotation;
}						t_input;

typedef struct s_texture_info
{
	SDL_Texture			*texture;
	int					height;
	int					width;
}						t_texture_info;

typedef struct s_textures
{

	t_texture_info		wall;
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
	t_textures			textures;
	SDL_Renderer		*renderer;
	int					wind_width;
	int					wind_height;
	t_float_xy			***vector_grid;
}						t_game;

# define FPS			game->fps
# define MAPS			game->maps
# define LEVEL			game->level
# define EVENT			game->event
# define ENEMY			game->ENEMY
# define PLAYER			game->player
# define WINDOW			game->window
# define RENDERER		game->renderer
# define KEYS			game->input.keys
# define WIND_WIDTH		game->wind_width
# define WIND_HEIGHT	game->wind_height
# define VECTOR_GRID	game->vector_grid
# define MOUSE_X		game->input.mouse_x_rel
# define PLAYER_X		game->player[(LEVEL)]->x
# define PLAYER_Y		game->player[(LEVEL)]->y
# define PLAYER_DIR_X	game->player[(LEVEL)]->dir.x
# define PLAYER_DIR_Y	game->player[(LEVEL)]->dir.y
# define PLAYER_CAM_X	game->player[(LEVEL)]->cam.x
# define PLAYER_CAM_Y	game->player[(LEVEL)]->cam.y
# define JOYSTICK_ROT	game->input.joystick_rotation
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
void					set_player_cam(t_game *game, int i);
void					init_raycaster_steps(t_raycaster *r);
void					chapter_1(t_game *game, int *running);
void					chapter_2(t_game *game, int *running);
void					chapter_3(t_game *game, int *running);
void					chapter_4(t_game *game, int *running);
void					chapter_5(t_game *game, int *running);
char					*strjoin(const char *s1, const char *s2);
void					handle_events(t_game *game, int *running);
void					init_raycaster(t_raycaster *r, t_game *game);
void					perform_raycaster_steps(t_raycaster *r, t_game *game);
void					draw_cercle(SDL_Renderer *renderer, int centerX, int centerY, int radius);
void					draw_column(SDL_Renderer *renderer, int x, int yStart, int yEnd, SDL_Color color);

#endif
