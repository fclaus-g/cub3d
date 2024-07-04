#include "../inc/cub3d.h"

void ft_init_ray_data(t_cub3d *cub)
{
	cub->ray.dir_x = 0;
	cub->ray.dir_y = 0;
	cub->ray.camera_x = 0;
	cub->ray.map_x = 0;
	cub->ray.map_y = 0;
	cub->ray.delta_dist_x = 0;
	cub->ray.delta_dist_y = 0;
	cub->ray.step_x = 0;
	cub->ray.step_y = 0;
	cub->ray.side_dist_x = 0;
	cub->ray.side_dist_y = 0;
	cub->ray.hit = 0;
	cub->ray.side = 0;
	cub->ray.perp_wall_dist = 0;
	cub->ray.line_height = 0;
	cub->ray.start_wall = 0;
	cub->ray.end_wall = 0;
}

void ft_print_ray_data(t_cub3d *cub)
{
	printf("dir_x = %f\n", cub->ray.dir_x);
	printf("dir_y = %f\n", cub->ray.dir_y);
	printf("camera_x = %f\n", cub->ray.camera_x);
	printf("map_x = %d\n", cub->ray.map_x);
	printf("map_y = %d\n", cub->ray.map_y);
	printf("delta_dist_x = %f\n", cub->ray.delta_dist_x);
	printf("delta_dist_y = %f\n", cub->ray.delta_dist_y);
	printf("step_x = %d\n", cub->ray.step_x);
	printf("step_y = %d\n", cub->ray.step_y);
	printf("side_dist_x = %f\n", cub->ray.side_dist_x);
	printf("side_dist_y = %f\n", cub->ray.side_dist_y);
	printf("hit = %d\n", cub->ray.hit);
	printf("side = %d\n", cub->ray.side);
	printf("perp_wall_dist = %f\n", cub->ray.perp_wall_dist);
	printf("line_height = %d\n", cub->ray.line_height);
	printf("start_wall = %d\n", cub->ray.start_wall);
	printf("end_wall = %d\n", cub->ray.end_wall);
}

void ft_raycaster(t_cub3d *cub)
{
	int x;

	x = 0;
	ft_init_ray_data(cub);
	//ft_print_ray_data(cub);
	while (x < WIDTH)
	{
		ft_prepare_ray(cub, x);
		//printf("ray x = %d, y = %d\n", cub->ray.x, cub->ray.y);
		cub->ray.map_x = (int)cub->player.x_pix/64;
		cub->ray.map_y = (int)cub->player.y_pix/64;
		ft_calc_hipotenusa(&cub->ray);
		ft_calc_player_hipotenusa(cub);
		ft_dda(cub);
		ft_wall_distance(cub);
		ft_identify_wall(cub);
		//ft_wall_x(cub);
		
		ft_paint_wall(cub, x);
		//mlx_image_to_window(cub->window, cub->window_canvas, 0, 0);
		
		//ft_print_algo(cub, x);
		//ft_print_ray_data(cub);
		x++;
	}
}

void ft_print_algo(t_cub3d *cub, int x)
{
	int y;
	int mid;


	y = HEIGHT;
	mid = HEIGHT / 2;
	while(y-- > mid)
	{
		mlx_put_pixel(cub->window_canvas, x, y, 0xff00ffff);
		//mlx_image_to_window(cub->window, cub->window_canvas, 0, 0);
	}
}

void ft_prepare_ray(t_cub3d *cub, int x)
{
	cub->ray.camera_x = 2 * x / (double)WIDTH - 1;
	printf("WIDTH = %d x = %d\n", WIDTH, x);
	printf("camera x = %f\n", cub->ray.camera_x);
	//cub->ray.x = cub->player.x_pix;
	//cub->ray.y = cub->player.y_pix;
	cub->ray.dir_x = cub->player.dir_x + cub->player.plane_x * cub->ray.camera_x;
	cub->ray.dir_y = cub->player.dir_y + cub->player.plane_y * cub->ray.camera_x;
	
	//printf("player dir x = %f y = %f\n", cub->player.dir_x, cub->player.dir_y);
	//printf("player plane x = %f y = %f\n", cub->player.plane_x, cub->player.plane_y);
 	//printf("ray dir x = %f y = %f\n", cub->ray.dir_x, cub->ray.dir_y);
// 	printf("ray map x = %d y = %d\n", cub->ray.map_x, cub->ray.map_y);
}

void ft_calc_hipotenusa(t_ray *ray)
{
	if (ray->dir_x == 0)
	{
		ray->delta_dist_x = INFINITE;
	}
	else
	{
		ray->delta_dist_x = fabs(1 / ray->dir_x);
		//printf("delta dist x: %f dir x = %f\n", ray->delta_dist_x, ray->dir_x);
	}
	if (ray->dir_y == 0)
	{
		ray->delta_dist_y = INFINITE;
	}
	else
	{
		ray->delta_dist_y = fabs(1 / ray->dir_y);
		//printf("delta dist y: %f ray y = %f\n", ray->delta_dist_y, ray->dir_y);
	}
	//printf("delta dist x: %f, delta dist y: %f\n", ray->delta_dist_x, ray->delta_dist_y);
}

void ft_calc_player_hipotenusa(t_cub3d *cub)
{
	if (cub->ray.dir_x < 0)
	{
		cub->ray.step_x = -1;
		cub->ray.side_dist_x = ((cub->player.x_pix/64) - cub->ray.map_x) * cub->ray.delta_dist_x;
		//printf("distancia hasta el muro = %f\n", cub->ray.side_dist_x);
	}
	else
	{
		cub->ray.step_x = 1;
		cub->ray.side_dist_x = (cub->ray.map_x + 1.0 - (cub->player.x_pix/64)) * cub->ray.delta_dist_x;
		//printf("distancia hasta el muro = %f\n", cub->ray.side_dist_x);
	}
	if (cub->ray.dir_y < 0)
	{
		cub->ray.step_y = -1;
		cub->ray.side_dist_y = ((cub->player.y_pix/64) - cub->ray.map_y) * cub->ray.delta_dist_y;
		//printf("distancia hasta el muro = %f\n", cub->ray.side_dist_y);
	}
	else
	{
		cub->ray.step_y = 1;
		cub->ray.side_dist_y = (cub->ray.map_y + 1.0 - (cub->player.y_pix/64)) * cub->ray.delta_dist_y;
		//printf("distancia hasta el muro = %f\n", cub->ray.side_dist_y);
	}
}

void ft_dda(t_cub3d *cub)
{
	cub->ray.hit = 0;
	//printf("CAracter en mapa %c \n", cub->map.map[cub->ray.map_y][cub->ray.map_x]);
	while (cub->ray.hit == 0)
	{
		if (cub->ray.side_dist_x < cub->ray.side_dist_y)
		{
			//printf("comp 1\n");
			cub->ray.side_dist_x += cub->ray.delta_dist_x;
			cub->ray.map_x += cub->ray.step_x;
			cub->ray.side = 0;
		}
		else
		{
			//printf("CAracter en mapa %c \n", cub->map.map[cub->ray.map_y][cub->ray.map_x]);
			//printf("comp 2\n");
			cub->ray.side_dist_y += cub->ray.delta_dist_y;
			cub->ray.map_y += cub->ray.step_y;
			cub->ray.side = 1;
			//printf("map x: %d, map y: %d\n", cub->ray.map_x, cub->ray.map_y);
		}
		if (cub->map.map[cub->ray.map_y][cub->ray.map_x] != '0')
		{
			//printf("hit------------------------------------------------------------\n");
			cub->ray.hit = 1;
		}
	}
}

void ft_wall_distance(t_cub3d * cub)
{
	if (cub->ray.side == 0)
	{
		cub->ray.perp_wall_dist = cub->ray.side_dist_x - cub->ray.delta_dist_x;
		//printf("perp wall dist = %fxxxxxxxxxxxxxxxxxx\n", cub->ray.perp_wall_dist);
	}
	else
	{
		cub->ray.perp_wall_dist = cub->ray.side_dist_y - cub->ray.delta_dist_y;
		//printf("perp wall dist = %f----------------------\n", cub->ray.perp_wall_dist);
	}
	cub->ray.line_height = (int)HEIGHT / cub->ray.perp_wall_dist;
	//printf("perp wall dist = %f, line height = %d\n", cub->ray.perp_wall_dist, cub->ray.line_height);

}

void ft_identify_wall(t_cub3d *cub)
{
	cub->ray.start_wall = ((-1) * cub->ray.line_height) / 2 + HEIGHT / 2;
	if (cub->ray.start_wall < 0)
	{
		cub->ray.start_wall = 0;
		//printf("start wall = %d\n", cub->ray.start_wall);
	}
	cub->ray.end_wall = cub->ray.line_height / 2 + HEIGHT / 2;
	if (cub->ray.end_wall >= cub->map.h_px)
	{
		cub->ray.end_wall = HEIGHT - 1;
		//printf("end wall = %d\n", cub->ray.end_wall);
	}
	//printf("start wall = %d, end wall = %d\n", cub->ray.start_wall, cub->ray.end_wall);
}

void ft_paint_wall(t_cub3d *cub, int x)
{
	int y;
	
	y = cub->ray.start_wall;
	//printf("pintando pared en columna en linea%d desde %d hasta %d\n", x, cub->ray.start_wall, cub->ray.end_wall);
	while (y < cub->ray.end_wall)
	{
		mlx_put_pixel(cub->window_canvas, x, y, 0xffff00ff);
		y++;
	}
}

void ft_wall_x(t_cub3d *cub)
{
	if (cub->ray.side == 0)
	{
		cub->ray.wall_x = cub->player.y_pix/64 + cub->ray.perp_wall_dist * cub->ray.dir_y;
	}
	else
	{
		cub->ray.wall_x = cub->player.x_pix/64 + cub->ray.perp_wall_dist * cub->ray.dir_x;
	}
	cub->ray.wall_x -= floor(cub->ray.wall_x);
}