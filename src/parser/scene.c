#include "../../inc/cub3d.h"

static int	is_scene_completed(t_cub3d *cub)
{
	return (cub->scene.textures.no != NULL
		&& cub->scene.textures.so != NULL
		&& cub->scene.textures.we != NULL
		&& cub->scene.textures.ea != NULL
		&& cub->scene.textures.floor.r != -1
		&& cub->scene.textures.ceil.r != -1
		&& cub->map.map != NULL
		&& cub->player.angle != -1);
}

static int	fill_cub_with_scene(t_cub3d *cub)
{
	cub->map.cols -= cub->map.left_padding;
	fill_map_matrix(cub);
	if (!is_scene_completed(cub))
	{
		show_error("Scene is missing required elements.");
		return (0);
	}
	if (!check_if_map_is_closed(cub))
	{
		show_error("Map is not closed.");
		return (0);
	}
	locate_player(cub);
	return (1);
}

int	read_and_parse_scene(char *path, t_cub3d *cub)
{
	int		fd;
	char	*line;
	char	*tmp;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		tmp = line;
		line = ft_strtrim(line, "\n");
		free(tmp);
		if (!validate_scene_line(line, cub))
		{
			free(line);
			end_read_fd(fd);
			return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (fill_cub_with_scene(cub));
}
