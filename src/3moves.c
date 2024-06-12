/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3moves.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:32:13 by fclaus-g          #+#    #+#             */
/*   Updated: 2024/06/12 17:50:01 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"


void ft_keys_moves(t_game *cub)
{
    	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(cub->mlx);
		exit (0);
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W) ||
		mlx_is_key_down(cub->mlx, MLX_KEY_UP))
		ft_move_up(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S)
		|| mlx_is_key_down(cub->mlx, MLX_KEY_DOWN))
		ft_move_down(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_A)
		|| mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
		ft_move_left(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D)
		|| mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
		ft_move_right(cub);
}

void	ft_move_up(t_game *cub)
{
	int y;
	int x;

	x =cub->player->instances[0].x;
	y =cub->player->instances[0].y;
	if (cub->map.map[(y - MOV) / PIX][(x + 10)/ PIX] != '1' 
		&& cub->map.map[(y - MOV) / PIX][(x + 50) / PIX] != '1')
	{
		if (cub->map.map[(y + 15 - MOV) / PIX][(x + 20)/ PIX] != 'E' 
			&& cub->map.map[(y + 15 - MOV) / PIX][(x + 40) / PIX] != 'E')
			ft_move_P_y(cub, -1);
	}

}

void	ft_move_P_y(t_game *cub, int direccion)
{
	if (direccion > 0)
		cub->player->instances[0].y += MOV;
	if (direccion < 0)
		cub->player->instances[0].y -= MOV;	
}

void	ft_move_P_x(t_game *cub, int direccion)
{
	if (direccion > 0)
		cub->player->instances[0].x += MOV;

	if (direccion < 0)
		cub->player->instances[0].x -= MOV;
}
void	ft_move_down(t_game *cub)
{
	int y;
	int x;

	x = cub->player->instances[0].x;
	y = cub->player->instances[0].y;
	if (cub->map.map[((y + 60) + MOV) / PIX][(x + 10) / PIX] != '1'
		&& cub->map.map[((y + 60) + MOV) / PIX][(x + 50) / PIX] != '1')
	{
		if(cub->map.map[((y + 55) + MOV) / PIX][(x + 25) / PIX] != 'E'
			&& cub->map.map[((y + 55) + MOV) / PIX][(x + 35) / PIX] != 'E')
			ft_move_P_y(cub, 1);
	}
}

void	ft_move_left(t_game *cub)
{
	int y;
	int x;

	x = cub->player->instances[0].x;
	y = cub->player->instances[0].y;
	//ft_player_direction(cub, 'L');
	if (cub->map.map[(y) / PIX][((x + 10) - MOV) / PIX] != '1'
		&& cub->map.map[((y + 60)) / PIX][((x + 10) - MOV) / PIX] != '1')
	{
		if (cub->map.map[(y + 10) / PIX][((x + 15) - MOV) / PIX] != 'E'
		&& cub->map.map[((y + 50)) / PIX][((x + 15) - MOV) / PIX] != 'E')
		ft_move_P_x(cub, -1);
	}
}

void	ft_move_right(t_game *cub)
{
	int y;
	int x;

	x = cub->player->instances[0].x;
	y = cub->player->instances[0].y;
	//ft_player_direction(cub, 'R');
	if (cub->map.map[(y) / PIX][((x + 50) + MOV)/ PIX] != '1'
		&& cub->map.map[((y + 60)) / PIX][((x + 50) + MOV) / PIX] != '1')
	{
		if (cub->map.map[(y + 10) / PIX][((x + 40) + MOV)/ PIX] != 'E'
		&& cub->map.map[((y + 50)) / PIX][((x + 40) + MOV) / PIX] != 'E')
		ft_move_P_x(cub, 1);
	}
}
