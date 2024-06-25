#include "../inc/cub3d.h"

void ft_init_minimap(t_game *cub)
{
	printf("Inicializando minimapa\n");

	// Crear una nueva imagen para el suelo
	cub->mini_w = cub->map.w_px / 4;
    cub->mini_h = cub->map.h_px / 4;
	cub->mini = mlx_new_image(cub->mlx, cub->mini_w, cub->mini_h);
	if (!cub->mini)
	{
		printf("Falló la creación de la imagen\n");
		exit(1);
	}
	ft_draw_map(cub);
	mlx_image_to_window(cub->mlx, cub->mini, 0, 0);
}

void	ft_init_map(t_game *cub)
{
	printf("Inicializando mapa\n");
	// Crear una nueva imagen para el suelo
	cub->pantalla = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->pantalla)
	{
		printf("Falló la creación de la pantalla\n");
		exit(1);
	}
	mlx_image_to_window(cub->mlx, cub->pantalla, 0, 0);
	ft_paint_floor_and_ceiling(&cub);
	//cargar texturas aqui
	ft_raycast(cub);	
}

void ft_draw_map(t_game *cub)
{
	int y;
	int x;

	y = -1;
	while (++y < cub->mini_h)
	{
		x = 0;
		while (++x < cub->mini_w)
		{
			if (cub->map.map[y / (PIX/4)][x / (PIX/4)] == '1')
				mlx_put_pixel(cub->mini, x, y, 0xff0000ff);
			else
				mlx_put_pixel(cub->mini, x, y, 0xff00ffff);	
		}
	}
}

void ft_draw_player(mlx_image_t *mini, int y, int x, int color)
{
	int i;
	int j;

	i = -1;
	while (++i < PLAYER_MINIMAP_SIZE / 4)
	{
		j = -1;
		while (++j < PLAYER_MINIMAP_SIZE / 4)
		{
			// printf("y: %d, x: %d\n", y + i, x + j);
			mlx_put_pixel(mini, x + j, y + i, color);
		}
	}
}

void ft_draw_square(mlx_image_t *canvas, int y, int x, int color)
{
	int i;
	int j;

	i = -1;
	if ((unsigned int)color != 0xffffffff)
	{
		while (++i < PIX)
		{
			j = -1;
			while (++j < PIX)
			{
				mlx_put_pixel(canvas, x + j, y + i, color);
			}
		}
	}
}

void ft_draw_ray(t_game *cub)
{
	int x;
	int y;
	double angle;
	int rays;

	//printf("Dibujando rayos\n");
	angle = cub->player.angle - VISION_ANGLE / 2;
	rays = 0;
	while (rays++ < VISION_NUM_RAYS)
	{
		x = cub->player.x + PLAYER_MINIMAP_SIZE / 2;
		y = cub->player.y + PLAYER_MINIMAP_SIZE / 2;
		//printf("Línea con ángulo: %f\n", angle);
		while (cub->map.map[y / PIX][x / PIX] != '1')
		{
			mlx_put_pixel(cub->mini, (int)(x / 4), (int)(y / 4), 0xffff0000);
			x += sin(angle) * 4;
			y -= cos(angle) * 4;
		}
		if (cub->map.map[y / PIX][x / PIX] == '1')
			ft_render_wall(cub, x, y, VISION_ANGLE);
		angle += VISION_ANGLE / (VISION_NUM_RAYS - 1);
	}
	//printf("Rayos dibujados\n");
}

void ft_render_wall(t_game *cub, int x, int y, double angle)
{
	// double distance;
	// double wall_height;
	// double plano_proyeccion;

	// plano_proyeccion = cub->map.w_px / (tan(VISION_ANGLE / 2));
	// distance = sqrt(pow(x - cub->player.x, 2) + pow(y - cub->player.y, 2));
	// wall_height = cub->map.h_px / distance * plano_proyeccion;
	(void)x;
	(void)y;
	(void)angle;
	ft_draw_wall(cub, VISION_NUM_RAYS);
}

void ft_draw_wall(t_game *cub, int rays)
{
	int start;
	int end;
	int painter;
	int mid;

	(void)rays;
	mid = HEIGHT / 2;
	// start is zero
	start = mid - HEIGHT / 2;
	if (start < 0)
		start = 0;
	// end is the height of the screen
	end = mid + HEIGHT / 2;
	if (end > HEIGHT)
		end = HEIGHT;
	painter = start;
	while (painter < end)
	{
		// printf("Pintando en x,y con mapa de %dx%d: %d, %d\n", WIDTH, HEIGHT, WIDTH / 2, painter);
		mlx_put_pixel(cub->pantalla, WIDTH / 2, painter, 0xffffffff);
		painter++;
	}
}

void ft_paint_floor_and_ceiling(t_game *cub)
{
	uint32_t y;
	uint32_t x;

	y = -1;
	while (++y < cub->pantalla->height / 2)
	{
		x = -1;
		while (++x < cub->pantalla->width)
		{
			mlx_put_pixel(cub->pantalla, x, y, 0x00ff00ff);
		}
	}
	y--;
	while (++y < cub->pantalla->height)
	{
		x = -1;
		while (++x < cub->pantalla->width)
		{
			mlx_put_pixel(cub->pantalla, x, y, 0xffffffff);
		}
	}
}