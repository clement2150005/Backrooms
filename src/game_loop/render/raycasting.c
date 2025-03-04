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

static int	store_mini_ray(t_mini_ray **head, t_raycaster r, char **map)
{
	t_mini_ray	*new_node;

	ray_has_hit_wall(&r);
	new_node = malloc(sizeof(t_mini_ray));
	if (!new_node)
		return (1);
	new_node->ray = r;
	new_node->ray.detected = map[r.map_y][r.map_x] - '0';
	new_node->next = *head;
	*head = new_node;
	return (0);
}
void	find_holes_minirays(t_mini_ray *head)
{
	int			hole_in_sequence;
	t_mini_ray	*current;

	current = head;
	hole_in_sequence = 0;
	while (current)
	{
		if (current->ray.detected == 10 && !hole_in_sequence)
		{
			current->ray.first_hole = 1;
			hole_in_sequence = 1;
		}
		else if (current->ray.detected == 10)
		{
			current->ray.first_hole = 0;
		}
		else
		{
			hole_in_sequence = 0;
			current->ray.first_hole = 0;
		}
		current = current->next;
	}
}


void	perform_raycaster_steps(t_raycaster *r, t_game *game)
{
	char	**map;

	r->mini_ray = NULL;
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
		
		if (store_mini_ray(&r->mini_ray, *r, MAPS[LEVEL]))
			cleanup(game);		
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
	find_holes_minirays(r->mini_ray);
	ray_has_hit_wall(r);
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
	r->cam_x = 2.0f * (float)r->x / (float)TEXTURE_WIDTH - 1.0f;
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
