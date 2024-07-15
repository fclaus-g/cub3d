#include "../inc/cub3d.h"

void	ft_keys_moves(t_cub3d *cub)
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
		ft_refresh_player(&cub->player, -1);
		if (cub->player.angle < 0)
		{
			cub->player.angle += 2 * M_PI;
		}
	}	
	if (mlx_is_key_down(cub->window, MLX_KEY_RIGHT))
	{
		cub->player.angle -= ROT_SPEED;
		ft_refresh_player(&cub->player, 1);
		if (cub->player.angle > 2 * M_PI)
		{
			cub->player.angle -= 2 * M_PI;
		}	
	}
}

void	ft_move_up(t_cub3d *cub)
{
	double	y;
	double	x;
	double	y_mov;
	double	x_mov;

	y_mov = -sin(cub->player.angle) * MOV;
	x_mov = cos(cub->player.angle) * MOV;
	y = cub->player.y_pix + y_mov;
	x = cub->player.x_pix + x_mov;
	if (!ft_check_collision(cub, x, y))
	{
		cub->player.y_pix = y;
		cub->player.x_pix = x;
	}
}

void	ft_move_down(t_cub3d *cub)
{
	double	y;
	double	x;
	double	y_mov;
	double	x_mov;

	y_mov = -sin(cub->player.angle + M_PI) * MOV;
	x_mov = cos(cub->player.angle + M_PI) * MOV;
	y = cub->player.y_pix + y_mov;
	x = cub->player.x_pix + x_mov;
	if (!ft_check_collision(cub, x, y))
	{
		cub->player.y_pix = y;
		cub->player.x_pix = x;
	}
}

void	ft_move_left(t_cub3d *cub)
{
	double	y;
	double	x;
	double	y_mov;
	double	x_mov;

	y_mov = -sin(cub->player.angle + M_PI / 2) * MOV;
	x_mov = cos(cub->player.angle + M_PI / 2) * MOV;
	y = cub->player.y_pix + y_mov;
	x = cub->player.x_pix + x_mov;
	if (!ft_check_collision(cub, x, y))
	{
		cub->player.y_pix = y;
		cub->player.x_pix = x;
	}
}

void	ft_move_right(t_cub3d *cub)
{
	double	y;
	double	x;
	double	y_mov;
	double	x_mov;

	y_mov = -sin(cub->player.angle - M_PI / 2) * MOV;
	x_mov = cos(cub->player.angle - M_PI / 2) * MOV;
	y = cub->player.y_pix + y_mov;
	x = cub->player.x_pix + x_mov;
	if (!ft_check_collision(cub, x, y))
	{
		cub->player.y_pix = y;
		cub->player.x_pix = x;
	}
}

int ft_check_collision(t_cub3d *cub, double x, double y)
{
	int grid_x_min = (int)(x - OFFSET) / GRID_SIZE;
	int grid_x_max = (int)(x + OFFSET) / GRID_SIZE;
	int grid_y_min = (int)(y - OFFSET) / GRID_SIZE;
	int grid_y_max = (int)(y + OFFSET) / GRID_SIZE;

	// Verifica todas las esquinas del jugador
	if (cub->map.map[grid_y_min][grid_x_min] == '1' || cub->map.map[grid_y_min][grid_x_max] == '1' ||
		cub->map.map[grid_y_max][grid_x_min] == '1' || cub->map.map[grid_y_max][grid_x_max] == '1')
	{
		return 1;
	}

	return 0;
}