#include "../inc/cub3d.h"

void ft_init_minimap(t_game *cub)
{
	printf("Inicializando mapa\n");

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
	double start_ray;
	double end_ray;
	double vision_angle;

	printf("Dibujando rayos\n");
	vision_angle = M_PI / 3;
	printf ("vision_angle: %f\n", vision_angle);
	start_ray = cub->player.angle - vision_angle / 2;
	printf("start_ray: %f\n", start_ray);
	end_ray = cub->player.angle + vision_angle / 2;
	printf("end_ray: %f\n", end_ray);

	while (start_ray < end_ray)
	{
		//printf("start_ray: %f\n", start_ray);
		x = cub->player.x + PLAYER_MINIMAP_SIZE / 2;
		y = cub->player.y + PLAYER_MINIMAP_SIZE / 2;
		while (cub->map.map[y / PIX][x / PIX] != '1')
		{

			mlx_put_pixel(cub->mini, x / 4, y / 4, 0x00ff00ff);
			x += sin(start_ray) * 4;
			y -= cos(start_ray) * 4;
		}
		ft_draw_view(cub);
		start_ray += 0.01;
	}
	
}

void ft_draw_view(t_game *cub)
{
	int start_y;
	int end_y;
	int mid_y;
	int count;

	count = 0;
	mid_y = cub->map.h_px / 2;
	start_y = mid_y - cub->map.h_px / 2;
	end_y = mid_y + cub->map.h_px / 2;
	count = start_y;
	while (count < start_y)
	{
		mlx_put_pixel(cub->view, NUM_RAYS, count, 0xffff00ff);
		count++;
	}
	while (count < end_y)
	{
		mlx_put_pixel(cub->view, NUM_RAYS, count, 0xffff70ff);
		count++;
	}
	while (count < cub->map.h_px)
	{
		mlx_put_pixel(cub->view, NUM_RAYS, count, 0xffffff);
	}



}

/*NOTAS PARA PINTAR LAS PAREDES

* Usando angulos:
-MACROS NECESARIAS:
ANCHO DE PANTALLA
ALTO DE PANTALLA
TILE_SIZE Es el tamaño de cada cuadro en el mapa (PIX)
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
