#include "../../inc/cub3d.h"

int	ft_check_collision(t_cub3d *cub, double x, double y)
{
	int	grid_x_min;
	int	grid_x_max;
	int	grid_y_min;
	int	grid_y_max;

	grid_x_min = (int)(x - OFFSET) / GRID_SIZE;
	grid_x_max = (int)(x + OFFSET) / GRID_SIZE;
	grid_y_min = (int)(y - OFFSET) / GRID_SIZE;
	grid_y_max = (int)(y + OFFSET) / GRID_SIZE;
	if (cub->map.map[grid_y_min][grid_x_min] == '1' || \
		cub->map.map[grid_y_min][grid_x_max] == '1' || \
		cub->map.map[grid_y_max][grid_x_min] == '1' || \
		cub->map.map[grid_y_max][grid_x_max] == '1')
	{
		return (1);
	}
	return (0);
}
