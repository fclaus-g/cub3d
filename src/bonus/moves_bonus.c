/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frgarcia <frgarcia@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:39:03 by frgarcia          #+#    #+#             */
/*   Updated: 2024/07/29 15:39:04 by frgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

void	ft_keys_moves(t_cub3d *cub)
{
	if (mlx_is_key_down(cub->window, MLX_KEY_ESCAPE))
	{
		mlx_close_window(cub->window);
		free_cub(cub);
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
		ft_rotate_player(cub, -1);
	if (mlx_is_key_down(cub->window, MLX_KEY_RIGHT))
		ft_rotate_player(cub, 1);
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
