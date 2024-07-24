#include "../../inc/cub3d_bonus.h"

void	ft_init_minimap(t_cub3d *cub)
{
	cub->mini.w = cub->window_canvas->width / 8;
	cub->mini.h = cub->mini.w;
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
	// int		grid_size;
	t_coord mini_start;
	t_coord	mini_coord;
	t_coord	grid_coord;
	t_coord	player;

	// grid_size = 1;
	player.x = (int)(cub->player.x_pix / GRID_SIZE);
	player.y = (int)(cub->player.y_pix / GRID_SIZE);
	printf("Player en posición (y=%d, x=%d)\n", player.y, player.x);

	mini_start.x = fmax(0, (int)(player.x - cub->mini.w / 2));
	mini_start.y = fmax(0, (int)(player.y - cub->mini.h / 2));
	printf("Comienzo a pintar mapa en (y=%d, x=%d)\n", mini_start.y, mini_start.x);
	// exit(0);


	mini_coord.y = -1;
	while (++mini_coord.y < cub->mini.h)
	{
		mini_coord.x = -1;
		grid_coord.y = (int)((mini_start.y + mini_coord.y) / GRID_SIZE);
		while (++mini_coord.x < cub->mini.w)
		{
			// printf("Coordenada minimap(y=%d, x=%d) grid(y=%d, x=%d)\n", mini_coord.y, mini_coord.x, grid_coord.y, grid_coord.x);
			grid_coord.x = (int)((mini_start.x + mini_coord.x) / GRID_SIZE);
			if (cub->map.map[grid_coord.y][grid_coord.x] == '1')
				mlx_put_pixel(cub->mini.canvas, mini_coord.x, mini_coord.y, 0xff0000ff);
			else
				mlx_put_pixel(cub->mini.canvas, mini_coord.x, mini_coord.y, 0xff00ffff);
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
