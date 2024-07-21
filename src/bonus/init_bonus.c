#include "../../inc/cub3d_bonus.h"

void	init_scene(t_cub3d *cub)
{
	cub->scene.textures.no = NULL;
	cub->scene.textures.so = NULL;
	cub->scene.textures.we = NULL;
	cub->scene.textures.ea = NULL;
	cub->scene.textures.floor.r = -1;
	cub->scene.textures.floor.g = -1;
	cub->scene.textures.floor.b = -1;
	cub->scene.textures.floor_path = NULL;
	cub->scene.textures.ceil.r = -1;
	cub->scene.textures.ceil.g = -1;
	cub->scene.textures.ceil.b = -1;
	cub->scene.textures.ceil_path = NULL;
	cub->scene.map_read_end = 0;
	cub->map.map = NULL;
	cub->map.lines = NULL;
	cub->map.left_padding = -1;
	cub->map.rows = 0;
	cub->map.cols = 0;
	cub->player.angle = -1;
	cub->hand = NULL;
}
