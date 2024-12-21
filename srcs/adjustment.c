/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjustment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 19:20:12 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/12/21 11:38:19 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	zoom_in_out(int keycode, t_data *data)
{
	if (keycode == XK_Shift_R)
	{
		if (data->zoom > 0)
			data->zoom -= ZOOM;
	}
	if (keycode == XK_Return)
	{
		if (data->zoom < (float)INT_MAX)
			data->zoom += ZOOM;
	}
}

void	adjust_alt(int keycode, t_data *data)
{
	if (keycode == XK_9)
	{
		if (data->flatten < 5)
			data->flatten += FLATTEN;
	}
	if (keycode == XK_0)
	{
		if (data->flatten > 0)
			data->flatten -= FLATTEN;
	}
}

void	rotation(int keycode, t_data *data)
{
	if (keycode == XK_1)
		data->rot_x += ROT;
	else if (keycode == XK_2)
		data->rot_x -= ROT;
	else if (keycode == XK_3)
		data->rot_y -= ROT;
	else if (keycode == XK_4)
		data->rot_y += ROT;
	else if (keycode == XK_5)
		data->rot_z += ROT;
	else if (keycode == XK_6)
		data->rot_z -= ROT;
}

void	translation(int keycode, t_data *data)
{
	if (keycode == XK_Up)
		data->shift_y -= TRANS;
	else if (keycode == XK_Left)
		data->shift_x -= TRANS;
	else if (keycode == XK_Right)
		data->shift_x += TRANS;
	else if (keycode == XK_Down)
		data->shift_y += TRANS;
}
