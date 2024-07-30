#include "../inc/cub3d.h"

/**
 * @brief prepare the data for raycasting and execute step to step
 * calcules for it
 * @param cub main struct
 */
void	ft_raycaster(t_cub3d *cub)
{
	int	x;

	x = 0;
	ft_init_ray_data(cub);
	while (x < WIDTH)
	{
		ft_prepare_ray(cub, x);
		cub->ray.map_x = (int)cub->player.x_pix;
		cub->ray.map_y = (int)cub->player.y_pix;
		ft_calc_hipotenusa(&cub->ray);
		ft_calc_player_hipotenusa(cub);
		ft_dda(cub);
		ft_wall_distance(cub);
		ft_wall_height(cub);
		ft_wall_x(cub);
		ft_paint_wall(cub, x);
		x++;
	}
}

/**
 * @brief prepare the ray data for the raycasting whit the x position 
 * ray.camera_x -> the posicion of the ray in the view
 * ray.dir.x/y -> the direction of the ray values between -1 and 1
 * ray.map_x/y -> the position of the ray in the map grid
 * @param cub 
 * @param x - x position of the ray
 *
  
 */
void	ft_prepare_ray(t_cub3d *cub, int x)
{
	cub->ray.camera_x = 2 * x / (double)WIDTH - 1;
	cub->ray.dir_x = cub->player.dir_x
		+ cub->player.plane_x * cub->ray.camera_x;
	cub->ray.dir_y = cub->player.dir_y
		+ cub->player.plane_y * cub->ray.camera_x;
	cub->ray.map_x = (int)cub->player.x_pix;
	cub->ray.map_y = (int)cub->player.y_pix;
}

/**
 * @brief calcule distance that the ray need to travel to hit a wall 
 * on the axis x and y
 * ray.dir_x/y-> the direction of the ray values between -1 and 1
 * ray.delta_dist_x/y -> the distance between the ray and the next wall
 * on the axis x or y whith values between 0 and 1
 *  * @param ray the ray to calculate
 */
void	ft_calc_hipotenusa(t_ray *ray)
{
	if (ray->dir_x == 0)
		ray->delta_dist_x = INFINITE;
	else
		ray->delta_dist_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = INFINITE;
	else
		ray->delta_dist_y = fabs(1 / ray->dir_y);
}

/**
 * @brief determine the direction of the ray and the distance to the next wall
 * if the ray is looking to the left the step is -1 and the distance is the
 * distance between the ray and the next wall on the x axis
 * cub->ray.side_dist_x = (player_position - map_grid_x) * distance_wall_x
 * @param cub 
 */
void	ft_calc_player_hipotenusa(t_cub3d *cub)
{
	if (cub->ray.dir_x < 0)
	{
		cub->ray.step_x = -1;
		cub->ray.side_dist_x = (cub->player.x_pix
				- cub->ray.map_x) * cub->ray.delta_dist_x;
	}
	else
	{
		cub->ray.step_x = 1;
		cub->ray.side_dist_x = (cub->ray.map_x + 1.0
				- cub->player.x_pix) * cub->ray.delta_dist_x;
	}
	if (cub->ray.dir_y < 0)
	{
		cub->ray.step_y = -1;
		cub->ray.side_dist_y = (cub->player.y_pix
				- cub->ray.map_y) * cub->ray.delta_dist_y;
	}
	else
	{
		cub->ray.step_y = 1;
		cub->ray.side_dist_y = (cub->ray.map_y + 1.0
				- cub->player.y_pix) * cub->ray.delta_dist_y;
	}
}

/**
 * * @brief perform the DDA algorithm to find the next wall that the ray will 
 * hit, if the distance to the next wall on the x axis is less than the 
 * distance to the next wall on the y axis the ray will move to the next wall
 * on the x axis and the side of the wall will be 0 if not the ray will move
 * to the next wall on the y axis and the side of the wall will be 1
 * @param cub 
 */
void	ft_dda(t_cub3d *cub)
{
	cub->ray.hit = 0;
	while (cub->ray.hit == 0)
	{
		if (cub->ray.side_dist_x < cub->ray.side_dist_y)
		{
			cub->ray.side_dist_x += cub->ray.delta_dist_x;
			cub->ray.map_x += cub->ray.step_x;
			cub->ray.side = 0;
		}
		else
		{
			cub->ray.side_dist_y += cub->ray.delta_dist_y;
			cub->ray.map_y += cub->ray.step_y;
			cub->ray.side = 1;
		}
		if (cub->map.map[cub->ray.map_y][cub->ray.map_x] == '1')
			cub->ray.hit = 1;
	}
}
