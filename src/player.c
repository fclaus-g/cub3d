#include "../inc/cub3d.h"

void ft_init_player(t_cub3d *cub)
{
	ft_player_orientation(&cub->player);
	//cub->player.x = cub->player.x_pix / GRID_SIZE;
	//cub->player.y = cub->player.y_pix / GRID_SIZE;
	//cub->player.dir_x = cos(cub->player.angle * M_PI / 180);
	//cub->player.dir_y = sin(cub->player.angle * M_PI / 180);
	printf ("dir_x = %f\n", cub->player.dir_x);
	printf ("dir_y = %f\n", cub->player.dir_y);

}