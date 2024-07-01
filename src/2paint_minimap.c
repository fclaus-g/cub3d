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
	printf("Pintando el suelo y el techo\n");
	ft_raycast(cub);
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
			if (cub->map.map[y / (GRID_SIZE/4)][x / (GRID_SIZE/4)] == '1')
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
	while (++i < GRID_SIZE / 4)
	{
		j = -1;
		while (++j < GRID_SIZE / 4)
			mlx_put_pixel(canvas, x + j, y + i, color);
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
	rays = 0;
	while (rays++ < NUM_RAYS)
	{
		//printf("Rayo %d en ángulo %f\n", rays, angle);
		x = cub->player.x_pix + GRID_SIZE / 2;
		y = cub->player.y_pix + GRID_SIZE / 2;
		//printf("Línea con ángulo: %f\n", angle);f
		while (cub->map.map[y / GRID_SIZE][x / GRID_SIZE] != '1')
		{
			mlx_put_pixel(cub->mini.canvas, (int)(x / 4), (int)(y / 4), 0xffff0000);
			x += sin(angle) * 20;
			y -= cos(angle) * 20;
		}
		angle += VISION_ANGLE / (NUM_RAYS - 1);

	}
	//printf("Rayos dibujados\n");
}

// void ft_render_wall(t_cub3d *cub, int x, int y, double angle)
// {
// 	// double distance;
// 	// double wall_height;
// 	// double plano_proyeccion;

// 	// plano_proyeccion = cub->map.w_px / (tan(VISION_ANGLE / 2));
// 	// distance = sqrt(pow(x - cub->player.x_pix, 2) + pow(y - cub->player.y_pix, 2));
// 	// wall_height = cub->map.h_px / distance * plano_proyeccion;
// 	(void)x;
// 	(void)y;
// 	(void)angle;
// 	ft_draw_wall(cub);
// }

// void ft_draw_wall(t_cub3d *cub, int rays)
// {
// 	int x;

// 	x = -1;
// 	while (++x < HEIGHT)
// 	{
// 		cub->camera_x = 2 * x / (double)WIDTH - 1;
// 		cub->dir_x = 
// 	}
// }

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

/*NOTAS PARA PINTAR LAS PAREDES

* Usando angulos:
-MACROS NECESARIAS:
ANCHO DE PANTALLA
ALTO DE PANTALLA
TILE_SIZE Es el tamaño de cada cuadro en el mapa (GRID_SIZE)
FOV es el angulo de vision
ROTATION_SPEED es la velocidad de rotacion
MOV_SPEED es la velocidad de movimiento (MOV)

-STRUCTS NECESARIAS:
t_player 
	int x;
	int y;
	double angle;
	float fov_rd; //angulo de vision en radianes
	int rotation //flag
	int mov_left_right //flag
	int mov_up_down //flag
t_ray
	double angle;
	double dist;
	int hit;//flag
Variables necesarias:


*/

double	ft_player_lookat_angle(char c)
{
	printf("Looking at angle %c\n", c);
	if (c == 'N')
		return (M_PI / 2);
	else if (c == 'S')
		return (M_PI * 3 / 2);
	else if (c == 'E')
		return (0);
	else if (c == 'W')
		return (M_PI);
	return (M_PI / 2);
}
