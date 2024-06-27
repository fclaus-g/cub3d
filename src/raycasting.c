#include "../inc/cub3d.h"

void paint_map(t_cub3d *cub)
{
	int	x;
	int camera_x;

	while (x < cub->map.w_px)
	{
		camera_x = 2 * x / (double)cub->map.w_px - 1;
		cub->ray.x = cub->dir.x + cub->plane.x * camera_x;
		cub->ray.y = cub->dir.y + cub->plane.y * camera_x;

		
	}
	
}