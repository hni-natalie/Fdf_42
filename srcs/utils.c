/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:46:31 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/12/21 11:48:54 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_arr(char **z_cor)
{
	int	i;

	i = -1;
	while (z_cor[++i])
		free(z_cor[i]);
	free(z_cor);
}

void	free_mem(t_map *map)
{
	int	i;

	if (!map)
		return ;
	if (map->height)
	{
		i = -1;
		while (++i < map->rows && map->height[i])
			free(map->height[i]);
		free(map->height);
	}
	if (map->color)
	{
		i = -1;
		while (++i < map->rows && map->color[i])
			free(map->color[i]);
		free(map->color);
	}
	free(map);
}

void	exit_error(char *msg)
{
	ft_printf("%s", RED);
	ft_printf(msg);
	ft_printf("\n");
	ft_printf("%s", RESET_COLOR);
	exit(1);
}

void	ft_calloc_arr(t_map *map)
{
	int	i;

	map->height = ft_calloc(map->rows, sizeof(int *));
	map->color = ft_calloc(map->rows, sizeof(int *));
	if (!map->height || !map->color)
	{
		free_mem(map);
		exit_error("Error: Fail to allocate memory.");
	}
	i = -1;
	while (++i < map->rows)
	{
		map->height[i] = ft_calloc(map->columns, sizeof(int));
		map->color[i] = ft_calloc(map->columns, sizeof(int));
		if (!map->height[i] || !map->color[i])
		{
			free_mem(map);
			exit_error("Error: Fail to allocate memory.");
		}
	}
}

int	ft_atoi_base(char *color, char *base)
{
	int	num;
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
	while ((*color <= '9' && *color >= '0')
		|| (ft_toupper(*color) >= 'A' && ft_toupper(*color) <= 'F'))
	{
		if (*color <= '9' && *color >= '0')
			num = num * ft_strlen(base) + (*color++ - '0');
		else
			num = num * ft_strlen(base) + (ft_toupper(*color++) - 55);
	}
	return (num * neg);
}
