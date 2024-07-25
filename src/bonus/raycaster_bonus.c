#include "../../inc/cub3d_bonus.h"

void	ft_raycaster(t_cub3d *cub)
{
	int	x;

	x = 0;
	ft_init_ray_data(cub);
	while (x < WIDTH)
	{
		ft_prepare_ray(cub, x);
		cub->ray.map.x = (int)cub->player.pos.x;
		cub->ray.map.y = (int)cub->player.pos.y;
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
	cub->ray.dir.x = cub->player.dir.x
		+ cub->player.plane.x * cub->ray.camera_x;
	cub->ray.dir.y = cub->player.dir.y
		+ cub->player.plane.y * cub->ray.camera_x;
	cub->ray.map.x = (int)cub->player.pos.x;
	cub->ray.map.y = (int)cub->player.pos.y;
}

void	ft_calc_hipotenusa(t_ray *ray)
{
	if (ray->dir.x == 0)
		ray->delta_dist.x = INFINITE;
	else
		ray->delta_dist.x = fabs(1 / ray->dir.x);
	if (ray->dir.y == 0)
		ray->delta_dist.y = INFINITE;
	else
		ray->delta_dist.y = fabs(1 / ray->dir.y);
}

void	ft_calc_player_hipotenusa(t_cub3d *cub)
{
	if (cub->ray.dir.x < 0)
	{
		cub->ray.step.x = -1;
		cub->ray.side_dist.x = (cub->player.pos.x
				- cub->ray.map.x) * cub->ray.delta_dist.x;
	}
	else
	{
		cub->ray.step.x = 1;
		cub->ray.side_dist.x = (cub->ray.map.x + 1.0
				- cub->player.pos.x) * cub->ray.delta_dist.x;
	}
	if (cub->ray.dir.y < 0)
	{
		cub->ray.step.y = -1;
		cub->ray.side_dist.y = (cub->player.pos.y
				- cub->ray.map.y) * cub->ray.delta_dist.y;
	}
	else
	{
		cub->ray.step.y = 1;
		cub->ray.side_dist.y = (cub->ray.map.y + 1.0
				- cub->player.pos.y) * cub->ray.delta_dist.y;
	}
}

void	ft_dda(t_cub3d *cub)
{
	cub->ray.hit = 0;
	while (cub->ray.hit == 0)
	{
		if (cub->ray.side_dist.x < cub->ray.side_dist.y)
		{
			cub->ray.side_dist.x += cub->ray.delta_dist.x;
			cub->ray.map.x += cub->ray.step.x;
			cub->ray.side = 0;
		}
		else
		{
			cub->ray.side_dist.y += cub->ray.delta_dist.y;
			cub->ray.map.y += cub->ray.step.y;
			cub->ray.side = 1;
		}
		if (cub->map.map[cub->ray.map.y][cub->ray.map.x] == '1')
			cub->ray.hit = 1;
	}
}
