/*==================================================================//
// 		 ____			  _								  			//
// 		|  _ \		  	 | |								 		//
// 		| |_) | __ _  ___| | ___ __ ___   ___  _ __ ___  ___ 		//
// 		|  _ < / _` |/ __| |/ | '__/ _ \ / _ \| '_ ` _ \/ __|		//
// 		| |_) | (_| | (__|   <| | | (_) | (_) | | | | | \__ \		//
// 		|____/ \__,_|\___|_|\_|_|  \___/ \___/|_| |_| |_|___/		//
//																	//
//			Author:   Clement Colin									//
//			Created:  February 6, 2025								//
//==================================================================*/

#include <backrooms.h>

static void	analyse_ray_data(t_raycaster *r)
{
	if (r->side)
	{
		if (r->ray_dir_y > 0)
		{
			r->wall_dir = SOUTH;
			return ;
		}
		r->wall_dir = NORTH;
		return ;
	}
	if (r->ray_dir_x > 0)
	{
		r->wall_dir = EAST;
		return ;
	}
	r->wall_dir = WEST;
}

static void	ray_has_hit_wall(t_raycaster *r)
{
	double	inv_ray_dir_x;
	double	inv_ray_dir_y;
	double	perp_dist;

	inv_ray_dir_x = 1.0f / r->ray_dir_x;
	inv_ray_dir_y = 1.0f / r->ray_dir_y;
	if (r->side == 0)
		r->perp_wall_dist = (r->map_x - r->pos_x + (1 - r->step_x) * 0.5f) * inv_ray_dir_x;
	else
		r->perp_wall_dist = (r->map_y - r->pos_y + (1 - r->step_y) * 0.5f) * inv_ray_dir_y;
	perp_dist = r->perp_wall_dist;
	r->wall_hit_x = r->pos_x + r->ray_dir_x * perp_dist;
	r->wall_hit_y = r->pos_y + r->ray_dir_y * perp_dist;
}

void	perform_raycaster_steps(t_raycaster *r, t_game *game)
{
	char	**map;

	map = MAPS[LEVEL];
	while (map[r->map_y][r->map_x] != WALL)
	{
		// if (map[r->map_y][r->map_x] == DOOR_CLOSED)
		// {
		// 	if (ray_has_hit_door(r, game))
		// 	{
		// 		r->wall_dir = DOOR;
		// 		return ;
		// 	}
		// }
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_dist_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_dist_y += r->delta_dist_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
	}
	ray_has_hit_wall(r);
	analyse_ray_data(r);
}

void	init_raycaster_steps(t_raycaster *r)
{
	if (r->ray_dir_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (r->pos_x - r->map_x) * r->delta_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0 - r->pos_x) * r->delta_dist_x;
	}
	if (r->ray_dir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (r->pos_y - r->map_y) * r->delta_dist_y;
		return ;
	}
	r->step_y = 1;
	r->side_dist_y = (r->map_y + 1.0 - r->pos_y) * r->delta_dist_y;
}

void	init_raycaster(t_raycaster *r, t_game *game)
{
	r->pos_x = PLAYER_X;
	r->pos_y = PLAYER_Y;
	r->map_x = (int)r->pos_x;
	r->map_y = (int)r->pos_y;
	r->cam_x = 2.0f * (float)r->x / (float)WIND_WIDTH - 1.0f;
	r->ray_dir_x = PLAYER_DIR_X + PLAYER_CAM_X * r->cam_x;
	r->ray_dir_y = PLAYER_DIR_Y + PLAYER_CAM_Y * r->cam_x;
	if (r->ray_dir_x == 0.0f)
		r->delta_dist_x = 1e10f;
	else
		r->delta_dist_x = fabsf(1.0f / r->ray_dir_x);
	if (r->ray_dir_y == 0.0f)
		r->delta_dist_y = 1e10f;
	else
		r->delta_dist_y = fabsf(1.0f / r->ray_dir_y);
}
