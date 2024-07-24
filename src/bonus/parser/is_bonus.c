#include "../../../inc/cub3d_bonus.h"

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (!is_map_space(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_rgb(t_rgb *color)
{
	if (color->r < 0 || color->r > 255)
		return (0);
	if (color->g < 0 || color->g > 255)
		return (0);
	if (color->b < 0 || color->b > 255)
		return (0);
	return (1);
}

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
