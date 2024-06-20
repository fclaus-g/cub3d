#include "../inc/cub3d.h"

void	print_player_position(t_game *cub)
{
	printf("Player -> x: %f, y: %f\n", cub->player.x, cub->player.y);
}

void ft_keys_moves(t_game *cub)
{
    	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(cub->mlx);
		exit (0);
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
		ft_move_up(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S))
		ft_move_down(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
		ft_move_left(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
		ft_move_right(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
		cub->player.angle -= 0.1;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
		cub->player.angle += 0.1;
}

void	ft_move_up(t_game *cub)
{
	int y;
	int x;

	x =cub->plyr->instances[0].x;
	y =cub->plyr->instances[0].y;
	if (cub->map.map[(y - MOV) / PIX][(x + 10)/ PIX] != '1' 
		&& cub->map.map[(y - MOV) / PIX][(x + 50) / PIX] != '1')
	{
		cub->plyr->instances[0].y -= MOV;
		cub->player.y = cub->player.y - MOV;
		print_player_position(cub);
	}
}

void	ft_move_down(t_game *cub)
{
	int y;
	int x;

	x = cub->plyr->instances[0].x;
	y = cub->plyr->instances[0].y;
	if (cub->map.map[((y + 60) + MOV) / PIX][(x + 10) / PIX] != '1'
		&& cub->map.map[((y + 60) + MOV) / PIX][(x + 50) / PIX] != '1')
	{
		cub->plyr->instances[0].y += MOV;
		cub->player.y += MOV;
		print_player_position(cub);
	}
}

void	ft_move_left(t_game *cub)
{
	int y;
	int x;

	x = cub->plyr->instances[0].x;
	y = cub->plyr->instances[0].y;
	if (cub->map.map[(y) / PIX][((x + 10) - MOV) / PIX] != '1'
		&& cub->map.map[((y + 60)) / PIX][((x + 10) - MOV) / PIX] != '1')
	{
		cub->plyr->instances[0].x -= MOV;
		cub->player.x -= MOV;
		print_player_position(cub);
	}
}

void	ft_move_right(t_game *cub)
{
	int y;
	int x;

	x = cub->plyr->instances[0].x;
	y = cub->plyr->instances[0].y;
	//ft_player_direction(cub, 'R');
	if (cub->map.map[(y) / PIX][((x + 50) + MOV)/ PIX] != '1'
		&& cub->map.map[((y + 60)) / PIX][((x + 50) + MOV) / PIX] != '1')
	{
		cub->plyr->instances[0].x += MOV;
		cub->player.x += MOV;
		print_player_position(cub);
	}
}
