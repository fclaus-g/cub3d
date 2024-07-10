#include "../inc/cub3d.h"

void	ft_wall_distance(t_cub3d * cub)
{
	if (cub->ray.side == 0)
	{
		cub->ray.perp_wall_dist = cub->ray.side_dist_x - cub->ray.delta_dist_x;
	}
	else
	{
		cub->ray.perp_wall_dist = cub->ray.side_dist_y - cub->ray.delta_dist_y;
	}
	cub->ray.line_height = (int)HEIGHT / cub->ray.perp_wall_dist;
}

void	ft_wall_height(t_cub3d *cub)
{
	cub->ray.start_wall = ((-1) * cub->ray.line_height) / 2 + HEIGHT / 2;
	if (cub->ray.start_wall < 0)
	{
		cub->ray.start_wall = 0;
	}
	cub->ray.end_wall = cub->ray.line_height / 2 + HEIGHT / 2;
	if (cub->ray.end_wall >= HEIGHT)
	{
		cub->ray.end_wall = HEIGHT - 1;
	}
}

uint32_t	ft_wall_color(t_cub3d *cub)
{
	if (cub->ray.side == 0)
	{
		if (cub->ray.step_x == 1)
			return (0xff0000ff);
		else
			return (0x00ff00ff);
	}
	else
	{
		if (cub->ray.step_y == 1)
			return (0x0000ffff);
		else
			return (0xffff00ff);
	}
}

void	ft_paint_wall(t_cub3d *cub, int x)
{
	int				y;
	mlx_texture_t	*aux;
	int				wall_height;
	int				calculated_x;
	int				calculated_y;
	// uint32_t color;

	aux = ft_choice_texture(cub);
	y = cub->ray.start_wall;
	wall_height = cub->ray.end_wall - cub->ray.start_wall;
	printf("Using texture %p\n", aux);
	while (y < cub->ray.end_wall)
	{
		calculated_y = (y - cub->ray.start_wall) * aux->height / wall_height;
		calculated_x = cub->ray.wall_x * aux->width;
		mlx_put_pixel(cub->window_canvas, x, y, get_pixel_color_from_texture(aux, calculated_x, calculated_y));
		y++;
	}
}

void	ft_wall_x(t_cub3d *cub)
{
	if (cub->ray.side == 0)
	{
		cub->ray.wall_x = cub->player.y_pix / GRID_SIZE + cub->ray.perp_wall_dist * cub->ray.dir_y;
		printf("cub->ray.wall_x = %f\n", cub->ray.wall_x);
	}
	else
	{
		cub->ray.wall_x = cub->player.x_pix / GRID_SIZE + cub->ray.perp_wall_dist * cub->ray.dir_x;
		printf("cub->ray.wall_x = %f\n", cub->ray.wall_x);
	}
	cub->ray.wall_x -= floor(cub->ray.wall_x);
}
