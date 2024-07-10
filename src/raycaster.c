#include "../inc/cub3d.h"

void	ft_raycaster(t_cub3d *cub)
{
	int	x;

	x = 0;
	ft_init_ray_data(cub);
	while (x < WIDTH)
	{
		ft_prepare_ray(cub, x);
		cub->ray.map_x = (int)cub->player.x_pix / GRID_SIZE;
		cub->ray.map_y = (int)cub->player.y_pix / GRID_SIZE;
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
 * @brief 
 * 
 * @param cub 
 * @param x - x position of the ray
 *
  
 */
void	ft_prepare_ray(t_cub3d *cub, int x)
{
	cub->ray.camera_x = 2 * x / (double)WIDTH - 1;
	cub->ray.dir_x = cub->player.dir_x + cub->player.plane_x * cub->ray.camera_x;
	cub->ray.dir_y = cub->player.dir_y + cub->player.plane_y * cub->ray.camera_x;
}

void	ft_calc_hipotenusa(t_ray *ray)
{
	if (ray->dir_x == 0)
	{
		ray->delta_dist_x = INFINITE;
	}
	else
	{
		ray->delta_dist_x = fabs(1 / ray->dir_x);
	}
	if (ray->dir_y == 0)
	{
		ray->delta_dist_y = INFINITE;
	}
	else
	{
		ray->delta_dist_y = fabs(1 / ray->dir_y);
	}
}

void	ft_calc_player_hipotenusa(t_cub3d *cub)
{
	if (cub->ray.dir_x < 0)
	{
		cub->ray.step_x = -1;
		cub->ray.side_dist_x = ((cub->player.x_pix / GRID_SIZE) - cub->ray.map_x) * cub->ray.delta_dist_x;
	}
	else
	{
		cub->ray.step_x = 1;
		cub->ray.side_dist_x = (cub->ray.map_x + 1.0 - (cub->player.x_pix / GRID_SIZE)) * cub->ray.delta_dist_x;
	}
	if (cub->ray.dir_y < 0)
	{
		cub->ray.step_y = -1;
		cub->ray.side_dist_y = ((cub->player.y_pix / GRID_SIZE) - cub->ray.map_y) * cub->ray.delta_dist_y;
	}
	else
	{
		cub->ray.step_y = 1;
		cub->ray.side_dist_y = (cub->ray.map_y + 1.0 - (cub->player.y_pix / GRID_SIZE)) * cub->ray.delta_dist_y;
	}
}

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
		if (cub->map.map[cub->ray.map_y][cub->ray.map_x] != '0')
		{
			cub->ray.hit = 1;
			cub->ray.wall_color = ft_wall_color(cub);
		}
	}
}
