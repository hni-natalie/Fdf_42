/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_algo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 17:58:20 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/12/23 12:05:18 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	draw_map(t_data *data)
{
	int	x;
	int	y;

	ft_bzero(data->img->addr, W_HEIGHT * W_WIDTH * (data->img->bpp / 8));
	y = -1;
	while (++y < data->map->rows)
	{
		x = -1;
		while (++x < data->map->columns)
		{
			if (x < data->map->columns - 1)
				bresenham(data,
					transform(data, new_point(x, y, data)),
					transform(data, new_point(x + 1, y, data)));
			if (y < data->map->rows - 1)
				bresenham(data,
					transform(data, new_point(x, y, data)),
					transform(data, new_point(x, y + 1, data)));
		}
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img->mlx_img, 0, 0);
	control_menu(data);
}

t_point	new_point(int x, int y, t_data *data)
{
	t_point	point;

	point.x = x;
	point.y = y;
	point.z = data->map->height[y][x];
	if (data->map->got_color)
		point.color = data->map->color[y][x];
	else
		point.color = cal_color(data, point.z);
	return (point);
}

void	init_bresenham(t_point start, t_point end, t_point *delta,
				t_point *sign)
{
	delta->x = ft_abs(end.x - start.x);
	delta->y = -ft_abs(end.y - start.y);
	sign->x = -1;
	sign->y = -1;
	if (start.x < end.x)
		sign->x = 1;
	if (start.y < end.y)
		sign->y = 1;
}

void	bresenham(t_data *data, t_point start, t_point end)
{
	int		error;
	int		tmp;
	t_point	sign;
	t_point	delta;

	init_bresenham(start, end, &delta, &sign);
	error = delta.x + delta.y;
	while (start.x != end.x || start.y != end.y)
	{
		put_pixel(data, start.x, start.y, get_color(start, end, delta));
		tmp = error * 2;
		if (tmp >= delta.y)
		{
			error += delta.y;
			start.x += sign.x;
		}
		if (tmp <= delta.x)
		{
			error += delta.x;
			start.y += sign.y;
		}
	}
}

void	put_pixel(t_data *data, int x, int y, int color)
{
	int	pixel;

	if (x >= W_WIDTH || y >= W_HEIGHT || x < 0 || y < 0)
		return ;
	pixel = (y * data->img->line_len) + (x * (data->img->bpp / 8));
	if (data->img->endian == 1)
	{
		data->img->addr[pixel + 0] = (color >> 24);
		data->img->addr[pixel + 1] = (color >> 16) & 0xFF;
		data->img->addr[pixel + 2] = (color >> 8) & 0xFF;
		data->img->addr[pixel + 3] = (color) & 0xFF;
	}
	else
	{
		data->img->addr[pixel + 0] = (color) & 0xFF;
		data->img->addr[pixel + 1] = (color >> 8) & 0xFF;
		data->img->addr[pixel + 2] = (color >> 16) & 0xFF;
		data->img->addr[pixel + 3] = (color >> 24);
	}
}
