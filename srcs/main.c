/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:05:46 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/12/17 16:31:40 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	int		len;
	t_map	*map;
	
	if (argc != 2 || (argc == 1 && !argv[1][0]))
		exit_error("Error: Incorrect number of argument.");
	len = ft_strlen(argv[1]);
	if (ft_strncmp(argv[1] + (len - 4), ".fdf", 4) != 0)
		exit_error("Error: Incorrect File Type. <map>.fdf");
	map = handle_map(argv[1]);
	free_mem(map);
	return (0);
}

t_map	*handle_map(char *file)
{
	int		fd;
	t_map	*map;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit_error("Error: File Can't be Opened.");
	map = ft_calloc(1, sizeof(t_map)); 
	if (!map)
		exit_error("Error: Fail to allocate memory for t_map");
	find_area(fd, map);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit_error("Error: File Can't be Opened");
	get_height_color(fd, map);
	close(fd);
	return (map);
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
			map->color[x][y] = convert_hex_color(z_cor[y]);
			printf("%d ", map->color[x][y]); //debug
		}
		free(line);
		free_arr(z_cor);
	}
}

int	convert_hex_color(char *color)
{
	while (ft_isdigit(*color) || *color == '-' || *color == '+'
		|| *color == ',')
		color++;
	if (*color++ == 'x')
		return (ft_atoi_base(color, HEXA_BASE));
	return (WHITE);
}

int	ft_atoi_base(char *color, char *base)
{
	int num;
	int	neg;

	num = 0;
	neg = 1;
	while (*color == ' ' || (*color >= 9 && *color <= 13))
		color++;
	if (*color == '-' || *color == '+')
	{
		if (*color++ == '-')
			neg = -1;
	}
	while ((*color <= '9' && *color >= '0') || 
		(ft_toupper(*color) >= 'A' && ft_toupper(*color) <= 'F'))
	{
		if (*color <= '9' && *color >= '0')
			num = num * ft_strlen(base) + (*color++ - '0');
		else
			num = num * ft_strlen(base) + (ft_toupper(*color++) - 55);
	}
	return (num);
}

int	min_max_z(int z, t_map *map)
{
	if (z < map->min_height)
		map->min_height = z;
	if (z > map->max_height)
		map->max_height = z;
	return (z);
}

void	find_area(int fd, t_map *map)
{
	char	*line;
	char	**x_axis;
	int		i;

	i = -1;
	line = get_next_line(fd);
	x_axis = ft_split(line, ' ');
	if (!x_axis || !*x_axis || !x_axis[0] || !x_axis[1])
	{
		free_mem(map);
		exit_error("Error: Empty & Invalid File.");
	}
	while(x_axis[++i])
		map->columns++;
	free_arr(x_axis);
	// printf("columns = %d\n", map->columns); //debug
	while (line)
	{
		map->rows++;
		free(line);
		line = get_next_line(fd);
	}
	// printf("rows = %d\n", map->rows); // debug
	free(line);
	close(fd);
}
