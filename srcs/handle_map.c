/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 09:04:33 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/12/24 13:58:05 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	find_area(int fd, t_map *map)
{
	char	*line;
	char	**x_axis;
	int		i;

	i = -1;
	line = get_next_line(fd);
	x_axis = ft_split(line, ' ');
	while (line)
	{
		map->rows++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	if (!x_axis || !*x_axis)
	{
		free(line);
		free_mem(map);
		exit_error("Error: Empty File. Ooops...");
	}
	find_width(line, x_axis, map);
	free_arr(x_axis);
	close(fd);
}

void	find_width(char *line, char **x_axis, t_map *map)
{
	int	len;

	if (x_axis[0][0] == '\n' || !x_axis[1])
	{
		free(line);
		free_arr(x_axis);
		free(map);
		exit_error("Error: Invalid file. Ooops...");
	}
	len = -1;
	while (x_axis[++len])
		map->columns++;
}

void	get_height_color(int fd, t_map *map)
{
	char	*line;
	char	**z_cor;
	int		x;
	int		y;

	x = -1;
	ft_calloc_arr(map);
	while (++x <= map->rows)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		z_cor = ft_split(line, ' ');
		y = -1;
		while (++y < map->columns)
		{
			map->height[x][y] = min_max_z(ft_atoi(z_cor[y]), map);
			map->color[x][y] = convert_hex_color(z_cor[y], map);
		}
		free(line);
		free_arr(z_cor);
	}
}

int	convert_hex_color(char *color, t_map *map)
{
	while (ft_isdigit(*color) || *color == '-' || *color == '+'
		|| *color == ',')
		color++;
	if (*color++ == 'x')
	{
		map->got_color = 1;
		return (ft_atoi_base(color, HEXA_BASE));
	}
	return (WHITE);
}

int	min_max_z(int z, t_map *map)
{
	if (z < map->min_height)
		map->min_height = z;
	if (z > map->max_height)
		map->max_height = z;
	return (z);
}
