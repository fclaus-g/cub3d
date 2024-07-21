#include "../../inc/cub3d_bonus.h"

void	ft_mouse_hook(enum mouse_key button, enum action accion, enum modifier_key tecla, void *param)
{
	// t_cub3d	*cub;

	(void)button;
	(void)accion;
	(void)tecla;
	(void)param;
	// Disparo
	// if (button == 1)
	// {
	// 	cub->player.shoot = 1;
	// }
}

void	ft_cursor_hook(double x, double y, void *param)
{
	t_cub3d	*cub;

	cub = (t_cub3d *)param;
	(void)x;
	(void)y;
	// if (cub->player.cursor_x < 0)
	// 	cub->player.cursor_x = 0;
	if (cub->cursor_x < x)
		ft_rotate_player(cub, 1);
	else if (cub->cursor_x > x)
		ft_rotate_player(cub, -1);
	cub->cursor_x = x;
}
