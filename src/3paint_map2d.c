#include "../inc/cub3d.h"

void ft_init_map2d(t_cub3d *cub)
{
	ft_load_images(cub);
	printf("Inicializando mapa\n");
	ft_render_wall_and_floor(cub);
	ft_render_player(cub);

}

void ft_load_images(t_cub3d *cub)
{
	mlx_texture_t *aux;

	aux = malloc(sizeof(mlx_texture_t));
	aux = mlx_load_png("texture/E.png");
	cub->wall = mlx_texture_to_image(cub->mlx, aux);
	mlx_delete_texture(aux);
	aux = mlx_load_png("texture/Nbyn.png");
	cub->floor = mlx_texture_to_image(cub->mlx, aux);
	mlx_delete_texture(aux);
	aux = mlx_load_png("texture/0.png");
	cub->plyr = mlx_texture_to_image(cub->mlx, aux);
	mlx_delete_texture(aux);
}

void ft_render_wall_and_floor(t_cub3d *cub)
{
	int y;
	int x;

	y = -1;
	while (++y < cub->map.rows)
	{
		x = -1;
		while (++x < cub->map.cols)
		{
			if (cub->map.map[y][x] == '1')
			{
				mlx_image_to_window(cub->mlx, cub->wall, x * PIX, y * PIX);
				mlx_set_instance_depth(&cub->wall->instances[cub->ins_wall], 5);
				cub->ins_wall++;
			}
			else if (cub->map.map[y][x] == '0' || ft_strchr("NSEW", cub->map.map[y][x]))
			{
				mlx_image_to_window(cub->mlx, cub->floor, x * PIX, y * PIX);
				mlx_set_instance_depth(&cub->floor->instances[cub->ins_floor], 1);
				cub->ins_floor++;
			}
		}
	}
}

double	ft_player_lookat_angle(char c)
{
	if (c == 'N')
		return (M_PI / 2);
	else if (c == 'S')
		return (M_PI * 3 / 2);
	else if (c == 'E')
		return (0);
	else if (c == 'W')
		return (M_PI);
	return (M_PI / 2);
}

void ft_find_player(t_cub3d *cub)
{
	int y;
	int x;

	y = -1;
	while(++y < cub->map.rows)
	{
		x = -1;
		while (++x < cub->map.cols)
		{
			if (ft_strchr("NSEW", cub->map.map[y][x]))
			{
				cub->player.x = x;
				cub->player.y = y;
				cub->player.angle = ft_player_lookat_angle(cub->map.map[y][x]);
				return ;
			}
		}
	}
}

void  ft_render_player(t_cub3d *cub)
{
	mlx_image_to_window(cub->mlx, cub->plyr, cub->player.x, cub->player.y);
	mlx_set_instance_depth(&cub->plyr->instances[0], 10);
}
