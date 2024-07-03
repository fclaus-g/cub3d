#include "../inc/cub3d.h"

void	print_player_position(t_cub3d *cub)
{
	printf("Player -> x: %f, y: %f\n", cub->player.x_pix, cub->player.y_pix);
}

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
	int y;
	int x;

	//printf("Moviendo hacia arriba\n");
	x = cub->player.x_pix;
	y = cub->player.y_pix;
	if (cub->map.map[(y - MOV) / GRID_SIZE][(x + 10)/ GRID_SIZE] != '1' 
		&& cub->map.map[(y - MOV) / GRID_SIZE][(x + 50) / GRID_SIZE] != '1')
	{
		cub->player.y_pix = cub->player.y_pix - MOV;
		// print_player_position(cub);
	}
}

void	ft_move_down(t_cub3d *cub)
{
	int y;
	int x;

	x = cub->player.x_pix;
	y = cub->player.y_pix;
	if (cub->map.map[((y + 60) + MOV) / GRID_SIZE][(x + 10) / GRID_SIZE] != '1'
		&& cub->map.map[((y + 60) + MOV) / GRID_SIZE][(x + 50) / GRID_SIZE] != '1')
	{
	 	cub->player.y_pix += MOV;
		//print_player_position(cub);
	}
}

void	ft_move_left(t_cub3d *cub)
{
	int y;
	int x;

	x = cub->player.x_pix;
	y = cub->player.y_pix;
	if (cub->map.map[(y) / GRID_SIZE][((x + 10) - MOV) / GRID_SIZE] != '1'
		&& cub->map.map[((y + 60)) / GRID_SIZE][((x + 10) - MOV) / GRID_SIZE] != '1')
	{
		cub->player.x_pix -= MOV;
		//print_player_position(cub);
	}
}

void	ft_move_right(t_cub3d *cub)
{
	int y;
	int x;

	x = cub->player.x_pix;
	y = cub->player.y_pix;
	//ft_player_direction(cub, 'R');
	if (cub->map.map[(y) / GRID_SIZE][((x + 50) + MOV)/ GRID_SIZE] != '1'
		&& cub->map.map[((y + 60)) / GRID_SIZE][((x + 50) + MOV) / GRID_SIZE] != '1')
	{
		cub->player.x_pix += MOV;
		//print_player_position(cub);
	}
}
