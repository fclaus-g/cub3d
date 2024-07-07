#include "../inc/cub3d.h"


void ft_keys_moves(t_cub3d *cub)
{
    if (mlx_is_key_down(cub->window, MLX_KEY_ESCAPE))
	{
		mlx_close_window(cub->window);
		exit (0);
	}
	if (mlx_is_key_down(cub->window, MLX_KEY_W))
		ft_move_up(cub);
	if (mlx_is_key_down(cub->window, MLX_KEY_S))
		ft_move_down(cub);
	if (mlx_is_key_down(cub->window, MLX_KEY_A))
		ft_move_left(cub);
	if (mlx_is_key_down(cub->window, MLX_KEY_D))
		ft_move_right(cub);
	if (mlx_is_key_down(cub->window, MLX_KEY_LEFT))
	{
		cub->player.angle += ROT_SPEED;
		ft_actualizar_jugador(&cub->player, -1);
		if (cub->player.angle < 0)
		{
			cub->player.angle += 2 * M_PI;
		}
	}	
	if (mlx_is_key_down(cub->window, MLX_KEY_RIGHT))
	{
		cub->player.angle -= ROT_SPEED;
		ft_actualizar_jugador(&cub->player, 1);
		if (cub->player.angle > 2 * M_PI)
		{
			cub->player.angle -= 2 * M_PI;
		}	
	
	}	
}

void	ft_move_up(t_cub3d *cub)
{
	double y;
	double x;
	double y_mov;
	double x_mov;

	y_mov = -sin(cub->player.angle) * MOV;
	x_mov = cos(cub->player.angle) * MOV;
	y = cub->player.y_pix + y_mov;
	x = cub->player.x_pix + x_mov;
	if (cub->map.map[(int)(y / GRID_SIZE)][(int)(x / GRID_SIZE)] != '1')
	{
		cub->player.y_pix = y;
		cub->player.x_pix = x;
	}
}

void	ft_move_down(t_cub3d *cub)
{
	double y;
	double x;
	double y_mov;
	double x_mov;

	y_mov = sin(cub->player.angle) * MOV;
	x_mov = -cos(cub->player.angle) * MOV;
	y = cub->player.y_pix + y_mov;
	x = cub->player.x_pix + x_mov;
	if (cub->map.map[(int)(y / GRID_SIZE)][(int)(x / GRID_SIZE)] != '1')
	{
		cub->player.y_pix = y;
		cub->player.x_pix = x;
	}
}

void	ft_move_left(t_cub3d *cub)
{
	double y;
	double x;
	double y_mov;
	double x_mov;

	y_mov = -sin(cub->player.angle + M_PI/2) * MOV;
	x_mov = cos(cub->player.angle + M_PI/2) * MOV;
	y = cub->player.y_pix + y_mov;
	x = cub->player.x_pix + x_mov;
	if (cub->map.map[(int)(y / GRID_SIZE)][(int)(x / GRID_SIZE)] != '1')
	{
		cub->player.y_pix = y;
		cub->player.x_pix = x;
	}
}

void	ft_move_right(t_cub3d *cub)
{
	double y;
	double x;
	double y_mov;
	double x_mov;

	y_mov = sin(cub->player.angle + M_PI/2) * MOV;
	x_mov = -cos(cub->player.angle + M_PI/2) * MOV;
	y = cub->player.y_pix + y_mov;
	x = cub->player.x_pix + x_mov;
	if (cub->map.map[(int)(y / GRID_SIZE)][(int)(x / GRID_SIZE)] != '1')
	{
		cub->player.y_pix = y;
		cub->player.x_pix = x;
	}
}
