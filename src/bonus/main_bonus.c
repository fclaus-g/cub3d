/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frgarcia <frgarcia@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:48:45 by frgarcia          #+#    #+#             */
/*   Updated: 2024/07/29 18:11:56 by frgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

void	ft_init_view(t_cub3d *cub)
{
	cub->window_canvas = mlx_new_image(cub->window, WIDTH, HEIGHT);
	if (!cub->window_canvas)
	{
		show_error("Map canvas creation failed\n");
		exit(1);
	}
	mlx_image_to_window(cub->window, cub->window_canvas, 0, 0);
	cub->map.map[(int)cub->player.y_pix][(int)cub->player.x_pix] = '0';
	ft_load_textures(cub);
	ft_paint_floor_and_ceiling(cub);
	ft_raycaster(cub);
}

void	ft_hook(void *param)
{
	t_cub3d	*cub;

	cub = (t_cub3d *)param;
	ft_keys_moves(cub);
	ft_draw_map(cub);
	ft_paint_floor_and_ceiling(cub);
	ft_raycaster(cub);
	if (cub->hand)
		ft_paint_hand(cub);
	if (cub->timer >= 0 && cub->timer <= 50)
		ft_paint_stats(cub, cub->sprite1);
	else if (cub->timer > 50 && cub->timer <= 100)
		ft_paint_stats(cub, cub->sprite2);
	else if (cub->timer > 100 && cub->timer <= 150)
		ft_paint_stats(cub, cub->sprite1);
	else if (cub->timer > 150 && cub->timer <= 200)
		ft_paint_stats(cub, cub->sprite3);
	else
	{
		ft_paint_stats(cub, cub->sprite1);
		cub->timer = 0;
	}
	cub->timer++;
}

int	main(int argc, char **argv)
{
	t_cub3d	cub;

	if (argc != 2)
	{
		show_error("Invalid number of arguments\n");
		exit(1);
	}
	init_cub(&cub);
	if (!validate_scene(argv[1], &cub))
	{
		free_cub(&cub);
		exit(1);
	}
	cub.window = mlx_init(WIDTH, HEIGHT, "cub3d", 0);
	cub.timer = 0;
	ft_init_view(&cub);
	ft_init_minimap(&cub);
	mlx_loop_hook(cub.window, &ft_hook, &cub);
	mlx_cursor_hook(cub.window, &ft_cursor_hook, &cub);
	mlx_loop(cub.window);
	free_cub(&cub);
	return (0);
}
