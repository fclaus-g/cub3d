#include "../../inc/cub3d_bonus.h"

void	ft_init_minimap(t_cub3d *cub)
{
	cub->mini.w = cub->map.w_px / 4;
	cub->mini.h = cub->map.h_px / 4;
	cub->mini.canvas = mlx_new_image(cub->window, cub->mini.w, cub->mini.h);
	if (!cub->mini.canvas)
	{
		show_error("Minimap canvas creation failed\n");
		exit(1);
	}
	ft_draw_map(cub);
	mlx_image_to_window(cub->window, cub->mini.canvas, 0, 0);
}

void	ft_draw_map(t_cub3d *cub)
{
	int	y;
	int	x;

	y = -1;
	while (++y < cub->mini.h)
	{
		x = 0;
		while (++x < cub->mini.w)
		{
			if (cub->map.map[(int)(y / (GRID_SIZE / 4))][(int)(x / (GRID_SIZE / 4 ))] == '1')
				mlx_put_pixel(cub->mini.canvas, x, y, 0xff0000ff);
			else
				mlx_put_pixel(cub->mini.canvas, x, y, 0xff00ffff);
		}
	}
}

void	ft_draw_player(mlx_image_t *canvas, int y, int x, int color)
{
	int	i;
	int	j;

	i = -1;
	x = x / 4 - GRID_SIZE / 16;
	y = y / 4 - GRID_SIZE / 16;
	while (++i < GRID_SIZE / 8)
	{
		j = -1;
		while (++j < GRID_SIZE / 8)
			mlx_put_pixel(canvas, x + j, y + i, color);
	}
}

void	ft_draw_square(mlx_image_t *canvas, int y, int x, int color)
{
	int	i;
	int	j;

	i = -1;
	if ((unsigned int)color != 0xffffffff)
	{
		while (++i < GRID_SIZE)
		{
			j = -1;
			while (++j < GRID_SIZE)
			{
				mlx_put_pixel(canvas, x + j, y + i, color);
			}
		}
	}
}

void	ft_draw_ray(t_cub3d *cub)
{
	int		x;
	int		y;
	double	angle;
	int		rays;

	//printf("Dibujando rayos\n");
	angle = cub->player.angle - VISION_ANGLE / 2;
	rays = 0;
	while (rays++ < NUM_RAYS)
	{
		x = cub->player.x_pix;
		y = cub->player.y_pix;
		while (cub->map.map[y / GRID_SIZE][x / GRID_SIZE] != '1')
		{
			mlx_put_pixel(cub->mini.canvas, (int)(x / 4), (int)(y / 4), 0xffff0000);
			x += cos(angle) * 20;
			y -= sin(angle) * 20;
		}
		angle += VISION_ANGLE / (NUM_RAYS - 1);
	}
}
