#include "../../inc/cub3d_bonus.h"

void	ft_print_player(t_cub3d *cub)
{
	printf("Player pixel position: %f, %f\n", cub->player.y_pix,
		cub->player.x_pix);
	printf("player grid position: %f, %f\n", cub->player.y, cub->player.x);
	printf("Player direction: %f, %f\n", cub->player.dir_y, cub->player.dir_x);
	printf("Player plane: %f, %f\n", cub->player.plane_y, cub->player.plane_x);
	printf("Player angle = %f\n", cub->player.angle);
}

void	ft_init_ray_data(t_cub3d *cub)
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

void	ft_print_ray_data(t_cub3d *cub)
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

void	free_cub(t_cub3d *cub)
{
	if (cub->scene.textures.no)
		free(cub->scene.textures.no);
	if (cub->scene.textures.so)
		free(cub->scene.textures.so);
	if (cub->scene.textures.we)
		free(cub->scene.textures.we);
	if (cub->scene.textures.ea)
		free(cub->scene.textures.ea);
	ft_lstclear(&cub->map.lines, free);
	ft_delete_textures(cub);
	free_matrix(cub->map.map);
	if (cub->window)
		mlx_terminate(cub->window);
}

void	ft_delete_textures(t_cub3d *cub)
{
	if (cub->no)
		mlx_delete_texture(cub->no);
	if (cub->so)
		mlx_delete_texture(cub->so);
	if (cub->we)
		mlx_delete_texture(cub->we);
	if (cub->ea)
		mlx_delete_texture(cub->ea);
	if (cub->hand)
		mlx_delete_texture(cub->hand);
}
