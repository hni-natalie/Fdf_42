/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 19:24:25 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/12/23 11:16:17 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

t_point	transform(t_data *data, t_point point)
{
	point.x *= data->zoom;
	point.y *= data->zoom;
	point.z *= (data->zoom / 10) * data->flatten;
	rot_x_y_z(data, &point.x, &point.y, &point.z);
	isometric(data, &point.x, &point.y, point.z);
	point.x += data->shift_x;
	point.y += data->shift_y;
	return (point);
}

void	rot_x_y_z(t_data *data, int *x, int *y, int *z)
{
	float	prev_x;
	float	prev_y;

	prev_y = *y;
	*y = (prev_y * (cos(data->rot_x))) - ((*z * sin(data->rot_x)));
	*z = (prev_y * sin(data->rot_x)) + (*z * cos(data->rot_x));
	prev_x = *x;
	*x = (*x * cos(data->rot_y)) + (*z * sin(data->rot_y));
	*z = -(prev_x * sin(data->rot_y)) + (*z * cos(data->rot_y));
	prev_x = *x;
	*x = (*x * cos(data->rot_z)) - (*y * sin(data->rot_z));
	*y = (prev_x * sin(data->rot_z)) + (*y * cos(data->rot_z));
}

void	isometric(t_data *data, int *x, int *y, int z)
{
	int	prev_x;

	prev_x = *x;
	if (!data->isometric)
		return ;
	*x = (*x - *y) * cos(0.52359877559);
	*y = -z + (prev_x + *y) * sin(0.52359877559);
}
