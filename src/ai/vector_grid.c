/*==================================================================//
// 		 ____			  _								  			//
// 		|  _ \		  	 | |								 		//
// 		| |_) | __ _  ___| | ___ __ ___   ___  _ __ ___  ___ 		//
// 		|  _ < / _` |/ __| |/ | '__/ _ \ / _ \| '_ ` _ \/ __|		//
// 		| |_) | (_| | (__|   <| | | (_) | (_) | | | | | \__ \		//
// 		|____/ \__,_|\___|_|\_|_|  \___/ \___/|_| |_| |_|___/		//
//																	//
//			Author:   Clement Colin									//
//			Created:  February 14, 2025								//
//==================================================================*/

#include <backrooms.h>

static t_float_xy	cast_single_ray(t_game *game, float start_x, float start_y, float end_x, float end_y)
{
	t_raycaster	r;
	char		**map;
	int			floored_x;
	int			floored_y;
	float		magnitude;

	floored_x = (int)floorf(end_x);
	floored_y = (int)floorf(end_y);
	r.pos_x = start_x;
	r.pos_y = start_y;
	r.map_x = (int)r.pos_x;
	r.map_y = (int)r.pos_y;
	r.ray_dir_x = end_x - start_x;
	r.ray_dir_y = end_y - start_y;
	magnitude = sqrtf(r.ray_dir_x * r.ray_dir_x + r.ray_dir_y * r.ray_dir_y);
	if (magnitude == 0)
		return ((t_float_xy){0, 0});
	r.ray_dir_x /= magnitude;
	r.ray_dir_y /= magnitude;
	r.delta_dist_x = (r.ray_dir_x == 0.0f) ? 1e10f : fabsf(1.0f / r.ray_dir_x);
	r.delta_dist_y = (r.ray_dir_y == 0.0f) ? 1e10f : fabsf(1.0f / r.ray_dir_y);
	if (r.ray_dir_x < 0)
	{
		r.step_x = -1;
		r.side_dist_x = (r.pos_x - r.map_x) * r.delta_dist_x;
	}
	else
	{
		r.step_x = 1;
		r.side_dist_x = (r.map_x + 1.0 - r.pos_x) * r.delta_dist_x;
	}
	if (r.ray_dir_y < 0)
	{
		r.step_y = -1;
		r.side_dist_y = (r.pos_y - r.map_y) * r.delta_dist_y;
	}
	else
	{
		r.step_y = 1;
		r.side_dist_y = (r.map_y + 1.0 - r.pos_y) * r.delta_dist_y;
	}
	map = MAPS[LEVEL];
	while (map[r.map_y][r.map_x] != WALL && map[r.map_y][r.map_x] != DOOR_CLOSED && (r.map_y != floored_y || r.map_x != floored_x))
	{
		if (r.side_dist_x < r.side_dist_y)
		{
			r.side_dist_x += r.delta_dist_x;
			r.map_x += r.step_x;
			r.side = 0;
		}
		else
		{
			r.side_dist_y += r.delta_dist_y;
			r.map_y += r.step_y;
			r.side = 1;
		}
	}
	if (map[r.map_y][r.map_x] == WALL)
		return ((t_float_xy){0, 0});
	return ((t_float_xy){r.ray_dir_x, r.ray_dir_y});
}

void	update_vector_grid(t_game *game)
{
	int			x;
	int			y;
	t_float_xy	vector;

	y = 0;
	while (MAPS[LEVEL][y])
	{
		x = 0;
		while (MAPS[LEVEL][y][x])
		{
			if (MAPS[LEVEL][y][x] == EMPTY)
			{
				vector = cast_single_ray(game, x + 0.5, y + 0.5, PLAYER_X, PLAYER_Y);
				if (vector.x != 0 && vector.y != 0)
				{
					VECTOR_GRID[LEVEL][y][x].x = vector.x;
					VECTOR_GRID[LEVEL][y][x].y = vector.y;
				}
			}
			x++;
		}
		y++;
	}
}
