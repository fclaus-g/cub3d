#include "../inc/cub3d.h"

void	print_player_position(t_cub3d *cub)
{
	printf("Player -> x: %f, y: %f\n", cub->player.x_pix, cub->player.y_pix);
}

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

void	ft_refresh_player(t_player *player, int girar)//----------------------------------Arreglar igualacion de variables
{
	double	oldDirX = player->dir_x;
	double	oldDirY = player->dir_y;
	double	oldPlaneX = player->plane_x;
	double	rotSpeed = girar * ROT_SPEED;

	player->dir_x = oldDirX * cos(rotSpeed) - oldDirY * sin(rotSpeed);
	player->dir_y = oldDirX * sin(rotSpeed) + oldDirY * cos(rotSpeed);
	player->plane_x = player->plane_x * cos(rotSpeed) - player->plane_y * sin(rotSpeed);
	player->plane_y = oldPlaneX * sin(rotSpeed) + player->plane_y * cos(rotSpeed);
}

/**
 * @brief prepara la orientacion del jugador que usaremos
 * en los calculos siguientes *
 * @param player
 */
void	ft_player_orientation(t_player *player)
{
	if (player->angle == M_PI / 2)
	{
		player->dir_x = 0;
		player->dir_y = -1;
		player->plane_x = 0.66;
		player->plane_y = 0;
		printf("player orientacion = 90 mira hacia el este x -1 plane y 0.66\n");
	}
	else if (player->angle == M_PI * 3 / 2)
	{
		player->dir_x = 0;
		player->dir_y = 1;
		player->plane_x = -0.66;
		player->plane_y = 0;
		printf("player orientacion = 270\n");
	}
	else if (player->angle == M_PI)
	{
		player->dir_x = -1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = 0.66;
		printf("player orientacion = 180\n");
	}
	else if (player->angle == 0)
	{
		player->dir_x = 1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = -0.66;
		printf("player orientacion = 0\n");
	}
}
