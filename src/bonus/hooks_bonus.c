/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frgarcia <frgarcia@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:34:28 by frgarcia          #+#    #+#             */
/*   Updated: 2024/07/29 16:03:39 by frgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

/**
 * @brief Unused function for the bonus
 * Ready to implement the shooting action
 */
/*
void	ft_mouse_hook(enum mouse_key button, enum action accion,
	enum modifier_key tecla, void *param)
{
	t_cub3d	*cub;

	(void)accion;
	(void)tecla;
	(void)param;
	if (button == 1)
		cub->player.shoot = 1;
}
*/

void	ft_cursor_hook(double x, double y, void *param)
{
	t_cub3d	*cub;

	cub = (t_cub3d *)param;
	(void)y;
	if (cub->cursor_x < x)
		ft_rotate_player(cub, 1);
	else if (cub->cursor_x > x)
		ft_rotate_player(cub, -1);
	cub->cursor_x = x;
}
