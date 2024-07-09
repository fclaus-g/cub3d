#include "../inc/cub3d.h"

void ft_init_minimap(t_cub3d *cub)
{
	// Crear una nueva imagen para el suelo
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

void	ft_init_map(t_cub3d *cub)
{
	cub->window_canvas = mlx_new_image(cub->window, WIDTH, HEIGHT);
	if (!cub->window_canvas)
	{
		show_error("Map canvas creation failed\n");
		exit(1);
	}
	mlx_image_to_window(cub->window, cub->window_canvas, 0, 0);
	cub->map.map[(int)cub->player.y_pix/GRID_SIZE][(int)cub->player.x_pix/GRID_SIZE] = '0';
	ft_paint_floor_and_ceiling(cub);
	//ft_init_player(cub);
	ft_print_player(cub);
	ft_load_textures(cub);
	ft_raycaster(cub);
}

void ft_draw_map(t_cub3d *cub)
{
	int y;
	int x;

	y = -1;
	while (++y < cub->mini.h)
	{
		x = 0;
		while (++x < cub->mini.w)
		{
			if (cub->map.map[(int)(y / (GRID_SIZE/4))][(int)(x / (GRID_SIZE/4))] == '1')
				mlx_put_pixel(cub->mini.canvas, x, y, 0xff0000ff);
			else
				mlx_put_pixel(cub->mini.canvas, x, y, 0xff00ffff);	
		}
	}
}

void ft_draw_player(mlx_image_t *canvas, int y, int x, int color)
{
	int i;
	int j;

	i = -1;
	x = x / 4;
	y = y / 4;
	while (++i < GRID_SIZE / 8)
	{
		j = -1;
		while (++j < GRID_SIZE / 8)
			mlx_put_pixel(canvas, x + 8 + j, y + 8 + i, color);
	}
}

void ft_draw_square(mlx_image_t *canvas, int y, int x, int color)
{
	int i;
	int j;

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

void ft_draw_ray(t_cub3d *cub)
{
	int x;
	int y;
	double angle;
	int rays;

	//printf("Dibujando rayos\n");
	angle = cub->player.angle - VISION_ANGLE / 2;
	//printf("---------------------angle es %f\n", angle);
	rays = 0;
	while (rays++ < NUM_RAYS)
	{
		//printf("Rayo %d en ángulo %f\n", rays, angle);
		x = cub->player.x_pix + GRID_SIZE / 4;
		y = cub->player.y_pix + GRID_SIZE / 4;
		//printf("Línea con ángulo: %f\n", angle);f
		while (cub->map.map[y / GRID_SIZE][x / GRID_SIZE] != '1')
		{
			mlx_put_pixel(cub->mini.canvas, (int)(x / 4 + 8), (int)(y / 4 + 8), 0xffff0000);
			x += cos(angle) * 20;
			y -= sin(angle) * 20;
		}
		angle += VISION_ANGLE / (NUM_RAYS - 1);

	}
	//printf("Rayos dibujados\n");
}


void ft_paint_floor_and_ceiling(t_cub3d *cub)
{
	uint32_t y;
	uint32_t x;

	y = -1;
	while (++y < cub->window_canvas->height / 2)
	{
		x = -1;
		while (++x < cub->window_canvas->width)
		{
			mlx_put_pixel(cub->window_canvas, x, y, 0x00ff00ff);
		}
	}
	y--;
	while (++y < cub->window_canvas->height)
	{
		x = -1;
		while (++x < cub->window_canvas->width)
		{
			mlx_put_pixel(cub->window_canvas, x, y, 0xffffffff);
		}
	}
	
}
void	ft_load_textures(t_cub3d *cub)
{
	cub->NO = malloc(sizeof(mlx_texture_t));
	cub->SO = malloc(sizeof(mlx_texture_t));
	cub->WE = malloc(sizeof(mlx_texture_t));
	cub->EA = malloc(sizeof(mlx_texture_t));
	if (!cub->NO || !cub->SO || !cub->WE || !cub->EA)
	{
		show_error("Texture allocation failed\n");
		exit(1);
	}
	cub->NO = mlx_load_png("textures/N.png");
	cub->SO = mlx_load_png("textures/S.png");
	cub->WE = mlx_load_png("textures/W.png");
	cub->EA = mlx_load_png("textures/E.png");
	printf("Textures loaded NO %p, SO %p, WE %p, EA %p\n", cub->NO, cub->SO, cub->WE, cub->EA);
}

