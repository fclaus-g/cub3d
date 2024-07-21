#include "../../inc/cub3d.h"

int	file_is_reachable(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int	cell_is_closed(t_cub3d *cub, int i, int j)
{
	if ((i == 0 || i == cub->map.rows - 1 || i == 0 || j == cub->map.cols - 1)
		|| (i > 0 && cub->map.map[i - 1][j] == MAP_FILL_SPACE)
		|| (i < cub->map.rows - 1 && cub->map.map[i + 1][j] == MAP_FILL_SPACE)
		|| (j > 0 && cub->map.map[i][j - 1] == MAP_FILL_SPACE)
		|| (j < cub->map.cols - 1 && cub->map.map[i][j + 1] == MAP_FILL_SPACE))
		return (0);
	return (1);
}

int	check_if_map_is_closed(t_cub3d *cub)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (i < cub->map.rows)
	{
		j = 0;
		while (j < cub->map.cols)
		{
			c = cub->map.map[i][j];
			if (c == '0' || is_map_player(c))
			{
				if (!cell_is_closed(cub, i, j))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

void	locate_player(t_cub3d *cub)
{
	int		i;
	int		j;

	i = 0;
	while (i < cub->map.rows)
	{
		j = 0;
		while (j < cub->map.cols)
		{
			if (is_map_player(cub->map.map[i][j]))
			{
				cub->player.x_pix = (j * GRID_SIZE) + (GRID_SIZE / 2);
				cub->player.y_pix = (i * GRID_SIZE) + (GRID_SIZE / 2);
				printf("Player located at (%f, %f) with angle %f\n",
					cub->player.x_pix, cub->player.y_pix, cub->player.angle);
				return ;
			}
			j++;
		}
		i++;
	}
}

/**
 * @brief continue reading the file descriptor until the end to avoid leaks
 * 
 * @param fd the file descriptor to read
 */
void	end_read_fd(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
