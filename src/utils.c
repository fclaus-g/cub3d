#include "../inc/cub3d.h"

void ft_print_player(t_cub3d *cub)
{
	printf("Player pixel position: %f, %f\n", cub->player.y_pix, cub->player.x_pix);
	printf("player grid position: %f, %f\n", cub->player.y, cub->player.x);
	printf("Player direction: %f, %f\n", cub->player.dir_y, cub->player.dir_x);
	printf("Player plane: %f, %f\n", cub->player.plane_y, cub->player.plane_x);
	printf("Player angle = %f\n", cub->player.angle);

}

void ft_actualizar_jugador(t_player *player, int girar)
{
    double oldDirX = player->dir_x;
	double oldDirY = player->dir_y;
    double oldPlaneX = player->plane_x;
    double rotSpeed = girar * ROT_SPEED; // Girar será 1 o -1 dependiendo de la dirección

    // Actualizar dirección
	player->dir_x = oldDirX * cos(rotSpeed) - oldDirY * sin(rotSpeed);
	player->dir_y = oldDirX * sin(rotSpeed) + oldDirY * cos(rotSpeed);
	printf("player dir x = %f y = %f\n", player->dir_x, player->dir_y);
    // Actualizar plano
    player->plane_x = player->plane_x * cos(rotSpeed) - player->plane_y * sin(rotSpeed);
    player->plane_y = oldPlaneX * sin(rotSpeed) + player->plane_y * cos(rotSpeed);
	//printf("player plane x = %f y = %f\n", player->plane_x, player->plane_y);
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
