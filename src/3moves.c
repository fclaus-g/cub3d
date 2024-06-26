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
		cub->player.angle -= 0.1;
	if (mlx_is_key_down(cub->window, MLX_KEY_RIGHT))
		cub->player.angle += 0.1;
}

void	ft_move_up(t_cub3d *cub)
{
	int y;
	int x;

	printf("Moviendo hacia arriba\n");
	x = cub->player.x_pix;
	y = cub->player.y_pix;
	if (cub->map.map[(y - MOV) / PIX][(x + 10)/ PIX] != '1' 
		&& cub->map.map[(y - MOV) / PIX][(x + 50) / PIX] != '1')
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
	if (cub->map.map[((y + 60) + MOV) / PIX][(x + 10) / PIX] != '1'
		&& cub->map.map[((y + 60) + MOV) / PIX][(x + 50) / PIX] != '1')
	{
	 	cub->player.y_pix += MOV;
		print_player_position(cub);
	}
}

void	ft_move_left(t_cub3d *cub)
{
	int y;
	int x;

	x = cub->player.x_pix;
	y = cub->player.y_pix;
	if (cub->map.map[(y) / PIX][((x + 10) - MOV) / PIX] != '1'
		&& cub->map.map[((y + 60)) / PIX][((x + 10) - MOV) / PIX] != '1')
	{
		cub->player.x_pix -= MOV;
		print_player_position(cub);
	}
}

void	ft_move_right(t_cub3d *cub)
{
	int y;
	int x;

	x = cub->player.x_pix;
	y = cub->player.y_pix;
	//ft_player_direction(cub, 'R');
	if (cub->map.map[(y) / PIX][((x + 50) + MOV)/ PIX] != '1'
		&& cub->map.map[((y + 60)) / PIX][((x + 50) + MOV) / PIX] != '1')
	{
		cub->player.x_pix += MOV;
		print_player_position(cub);
	}
}
