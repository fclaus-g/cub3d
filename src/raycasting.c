#include "../inc/cub3d.h"

/**
 * @brief Inicia el raycasting
 * 
 * @param cub  Estructura principal del juego
 */
void ft_raycast(t_cub3d *cub)
{
	int	x;

	x = 0;
	cub->wall = mlx_new_image(cub->window, WIDTH, HEIGHT);
	if (mlx_image_to_window(cub->window, cub->wall, 0, 0) == -1)
	{
		printf("Error\n");
	}
	ft_init_ray_data(cub);
	printf("raycasting\n");
	while (x < cub->map.w_px)
	{
		ft_player_orientation(&cub->player);
		ft_prepare_ray(cub, x);
		printf("ray prepared\n");
		ft_calc_hipotenusa(&cub->ray);
		printf("hipotenusa calculated\n");
		ft_calc_player_hipotenusa(cub);
		printf("player hipotenusa calculated\n");
		ft_dda(cub);
		printf("dda\n");
		ft_wall_distance(cub);
		printf("wall distance++++++++++++++++++++++++++++++++++++++++++++\n");
		ft_identify_wall(cub);
		printf("wall identified\n");
		ft_paint_wall(cub, x);
		printf("wall painted\n");
		x++;
		printf("x: %d\n", x);
	}
	
}
/**
 * @brief prepara la orientacion del jugador que usaremos
 * en los calculos siguientes * 
 * @param player 
 */
void ft_player_orientation(t_player *player)
{
	if (player->angle == M_PI / 2)
	{
		player->dir_x = -1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = 0.66;
		printf("player orientacion = 90\n");
	}
	else if (player->angle == M_PI * 3 / 2)
	{
		player->dir_x = 1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = -0.66;
		printf("player orientacion = 270\n");
	}
	else if (player->angle == M_PI)
	{
		player->dir_x = 0;
		player->dir_y = -1;
		player->plane_x = -0.66;
		player->plane_y = 0;
		printf("player orientacion = 180\n");
	}	
	else if (player->angle == 0)
	{
		player->dir_x = 0;
		player->dir_y = 1;
		player->plane_x = 0.66;
		player->plane_y = 0;
		printf("player orientacion = 0\n");
	}
}

/**
 * @brief Prepara el rayo para el raycasting 
 * En esta funcion se calcula la posicion de la camara(x)
 * 
 * @param cub Estructura principal del juego
 * @param x Coordenada x del rayo (linea vertical en la pantalla)
 */

void ft_prepare_ray(t_cub3d *cub, int x)
{
	cub->ray.camera_x = 2 * x / (double)cub->map.w_px - 1;
	cub->ray.x = cub->player.x_pix;
	cub->ray.y = cub->player.y_pix;
	cub->ray.dir_x = cub->player.dir_x + cub->player.plane_x * cub->ray.camera_x;
	cub->ray.dir_y = cub->player.dir_y + cub->player.plane_y * cub->ray.camera_x;
	cub->ray.map_x = (int)cub->player.x_pix / 64;
	cub->ray.map_y = (int)cub->player.y_pix / 64;
}

/**
 * @brief Calcula la hipotenusa del rayo
 * 
 * @param ray Estructura del rayo
 */
void ft_calc_hipotenusa(t_ray *ray)
{
	if (ray->dir_x == 0)
	{
		ray->delta_dist_x = INFINITE;
	}
	else
	{
		ray->delta_dist_x = fabs(1 / ray->dir_x);
		printf("delta dist x: %f\n", ray->delta_dist_x);
	}
	if (ray->dir_y == 0)
	{
		ray->delta_dist_y = INFINITE;
	}
	else
	{
		ray->delta_dist_y = fabs(1 / ray->dir_y);
		printf("delta dist y: %f\n", ray->delta_dist_y);
	}
}

void ft_calc_player_hipotenusa(t_cub3d *cub)
{
	if (cub->ray.dir_x < 0)
	{
		cub->ray.step_x = -1;
		cub->ray.side_dist_x = (cub->ray.x - cub->ray.map_x) * cub->ray.delta_dist_x;
		printf("distancia hasta el muro = %f\n", cub->ray.side_dist_x);
	}
	else
	{
		cub->ray.step_x = 1;
		cub->ray.side_dist_x = (cub->ray.map_x + 1.0 - cub->ray.x) * cub->ray.delta_dist_x;
		printf("distancia hasta el muro = %f\n", cub->ray.side_dist_x);
	}
	if (cub->ray.dir_y < 0)
	{
		cub->ray.step_y = -1;
		cub->ray.side_dist_y = (cub->ray.y - cub->ray.map_y) * cub->ray.delta_dist_y;
		printf("distancia hasta el muro = %f\n", cub->ray.side_dist_y);
	}
	else
	{
		cub->ray.step_y = 1;
		cub->ray.side_dist_y = (cub->ray.map_y + 1.0 - cub->ray.y) * cub->ray.delta_dist_y;
		printf("distancia hasta el muro = %f\n", cub->ray.side_dist_y);
	}
}
/**
 * @brief Algoritmo DDA (Digital Differential Analyzer)
 * 
 * @param cub Estructura principal del juego
 */

void ft_dda(t_cub3d *cub)
{
	cub->ray.hit = 0;
	printf("CAracter en mapa %c \n", cub->map.map[cub->ray.map_y][cub->ray.map_x]);
	while (cub->ray.hit == 0)
	{
		if (cub->ray.side_dist_x < cub->ray.side_dist_y)
		{
			printf("comp 1\n");
			cub->ray.side_dist_x += cub->ray.delta_dist_x;
			cub->ray.map_x += cub->ray.step_x;
			cub->ray.side = 0;
		}
		else
		{
			//printf("CAracter en mapa %c \n", cub->map.map[cub->ray.map_y][cub->ray.map_x]);
			//printf("comp 2\n");
			cub->ray.side_dist_y += cub->ray.delta_dist_y;
			cub->ray.map_y += cub->ray.step_y;
			cub->ray.side = 1;
			//printf("map x: %d, map y: %d\n", cub->ray.map_x, cub->ray.map_y);
		}
		if (cub->map.map[cub->ray.map_y][cub->ray.map_x] != '0')
		{
			printf("hit------------------------------------------------------------\n");
			cub->ray.hit = 1;
			break;
		}
	}
}



/**
 * @brief Calcula la distancia de la pared
 * 
 * @param cub Estructura principal del juego
 */
void ft_wall_distance(t_cub3d * cub)
{
	if (cub->ray.side == 0)
	{
		cub->ray.perp_wall_dist = (cub->ray.map_x - cub->ray.x + (1 - cub->ray.step_x) / 2) / cub->ray.dir_x;
	}
	else
	{
		cub->ray.perp_wall_dist = (cub->ray.map_y - cub->ray.y + (1 - cub->ray.step_y) / 2) / cub->ray.dir_y;
	}
	cub->ray.line_height = (int)(cub->map.h_px / cub->ray.perp_wall_dist);

}
/**
 * @brief idetifica el pixel de inicio y fin de la pared
 * 
 * @param cub 
 */

void ft_identify_wall(t_cub3d *cub)
{
	cub->ray.start_wall = -cub->ray.line_height / 2 + cub->map.h_px / 2;
	if (cub->ray.start_wall < 0)
	{
		cub->ray.start_wall = 0;
	}
	cub->ray.end_wall = cub->ray.line_height / 2 + cub->map.h_px / 2;
	if (cub->ray.end_wall >= cub->map.h_px)
	{
		cub->ray.end_wall = cub->map.h_px - 1;
	}
}

void ft_paint_wall(t_cub3d *cub, int x)
{
	int y;

	y = cub->ray.start_wall;
	while (y < cub->ray.end_wall)
	{
		if (cub->ray.side == 0)
		{
			printf("rayo horizontal\n");
			mlx_put_pixel(cub->wall, x, y, 0xffFF00ff);
		}
		else
		{
			printf("rayo vertical\n");
			mlx_put_pixel(cub->wall, x, y, 0xff00FFff);
		}
		mlx_image_to_window(cub->window, cub->wall, x, y);
		y++;
	}

}

void ft_init_ray_data(t_cub3d *cub)
{
	cub->ray.dir_x = 0;
	cub->ray.dir_y = 0;
	cub->ray.camera_x = 0;
	cub->ray.map_x = 0;
	cub->ray.map_y = 0;
	cub->ray.delta_dist_x = 0;
	cub->ray.delta_dist_y = 0;
	cub->ray.step_x = 0;
	cub->ray.step_y = 0;
	cub->ray.side_dist_x = 0;
	cub->ray.side_dist_y = 0;
	cub->ray.hit = 0;
	cub->ray.side = 0;
	cub->ray.perp_wall_dist = 0;
	cub->ray.line_height = 0;
	cub->ray.start_wall = 0;
	cub->ray.end_wall = 0;
}