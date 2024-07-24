#include "../../inc/cub3d_bonus.h"

int	is_cardinal_line(char *line)
{
	return (starts_with_and_space(line, "NO")
		|| starts_with_and_space(line, "SO")
		|| starts_with_and_space(line, "WE")
		|| starts_with_and_space(line, "EA"));
}

static void	ft_print_map_line(void *str)
{
	printf("\"%s\"\n", (char *)str);
}

void	print_scene(t_cub3d *cub)
{
	int	i;

	printf("NO: %s\n", cub->scene.textures.no);
	printf("SO: %s\n", cub->scene.textures.so);
	printf("WE: %s\n", cub->scene.textures.we);
	printf("EA: %s\n", cub->scene.textures.ea);
	printf("F: %d,%d,%d\n", cub->scene.textures.floor.r,
		cub->scene.textures.floor.g, cub->scene.textures.floor.b);
	printf("C: %d,%d,%d\n", cub->scene.textures.ceil.r,
		cub->scene.textures.ceil.g, cub->scene.textures.ceil.b);
	printf("Lines:\n");
	ft_lstiter(cub->map.lines, &ft_print_map_line);
	printf("Map (%dx%d), padding_left_remove(%d):\n",
		cub->map.rows, cub->map.cols, cub->map.left_padding);
	if (cub->map.map == NULL)
		printf("NULL\n");
	else
	{
		i = 0;
		while (cub->map.map[i] != NULL)
		{
			ft_print_map_line(cub->map.map[i]);
			i++;
		}
	}
}
