#include "../../inc/cub3d_bonus.h"

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

void	ft_refresh_player(t_player *player, int girar)
{
	double	old_dirx;
	double	old_diry;
	double	old_planex;
	double	rot_speed;

	old_dirx = player->dir_x;
	old_diry = player->dir_y;
	old_planex = player->plane_x;
	rot_speed = girar * ROT_SPEED;
	player->dir_x = old_dirx * cos(rot_speed) - old_diry * sin(rot_speed);
	player->dir_y = old_dirx * sin(rot_speed) + old_diry * cos(rot_speed);
	player->plane_x = player->plane_x * \
	cos(rot_speed) - player->plane_y * sin(rot_speed);
	player->plane_y = old_planex * \
	sin(rot_speed) + player->plane_y * cos(rot_speed);
}

/**
 * @brief prepare the orientation of the player that we will use
 * to calculate the rays
 * @param player
 */
void	ft_player_orientation(t_player *player)
{
	player->dir_x = 0;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0;
	if (player->angle == M_PI / 2)
	{
		player->dir_y = -1;
		player->plane_x = 0.66;
	}
	else if (player->angle == M_PI * 3 / 2)
	{
		player->dir_y = 1;
		player->plane_x = -0.66;
	}
	else if (player->angle == M_PI)
	{
		player->dir_x = -1;
		player->plane_y = 0.66;
	}
	else if (player->angle == 0)
	{
		player->dir_x = 1;
		player->plane_y = -0.66;
	}
}

void	ft_rotate_player(t_cub3d *cub, int direction)
{
	cub->player.angle += direction * ROT_SPEED * -1;
	ft_refresh_player(&cub->player, direction);
	if (direction == -1 && cub->player.angle < 0)
		cub->player.angle += 2 * M_PI;
	else if (direction == 1 && cub->player.angle > 2 * M_PI)
		cub->player.angle -= 2 * M_PI;
}
