/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 17:54:13 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/12/23 12:48:48 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	cal_color(t_data *data, int height)
{
	float	percentage;

	percentage = color_percentage(data->map->min_height,
			data->map->max_height, height);
	if (data->change_color)
	{
		if (percentage < 0.5)
			return (M_PINK);
		else
			return (M_PURPLE);
	}
	else
	{
		if (percentage < 0.5)
			return (M_PURPLE);
		else
			return (M_PINK);
	}
}

float	color_percentage(int min, int max, int current)
{
	int	range;
	int	position;

	range = max - min;
	position = current - min;
	if (range == 0)
		return (1.0);
	return (position / range);
}

int	get_color(t_point start, t_point end, t_point delta)
{
	int		r;
	int		b;
	int		g;
	float	percent;

	if (delta.x > delta.y)
		percent = color_percentage(start.x, end.x, start.x);
	else
		percent = color_percentage(start.y, end.y, start.y);
	r = partial_color((start.color >> 16) & 0xFF,
			(end.color >> 16) & 0xFF, percent);
	g = partial_color((start.color >> 8) & 0xFF,
			(end.color >> 8) & 0xFF, percent);
	b = partial_color(start.color & 0xFF, end.color & 0xFF, percent);
	return ((r << 16) | (g << 8) | b);
}

int	partial_color(int start, int end, float percent)
{
	return ((int)((1 - percent) * start + percent * end));
}
