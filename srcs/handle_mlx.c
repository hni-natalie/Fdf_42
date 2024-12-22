/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mlx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:03:02 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/12/21 11:45:55 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_data	*init_data(t_map *map)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		exit_error("Error: Fail to allocate memory for t_data.");
	data->img = ft_calloc(1, sizeof(t_img));
	if (!(data->img))
		exit_error("Error: Fail to allocate memory for t_img.");
	data->map = map;
	data->change_color = 0;
	set_default(data);
	return (data);
}

void	set_default(t_data *data)
{
	data->zoom = ft_greater((W_WIDTH / data->map->columns / 2),
			(W_HEIGHT / data->map->rows / 2));
	data->shift_x = (W_WIDTH - (data->map->columns * data->zoom));
	data->shift_y = (W_HEIGHT - (data->map->rows * data->zoom)) / 4;
	data->rot_x = 0;
	data->rot_y = 0;
	data->rot_z = 0;
	data->isometric = 1;
	data->flatten = 1;
}

int	ft_greater(int x, int y)
{
	if (x > y)
		return (x);
	else
		return (y);
}

void	init_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
	{
		free_mem(data->map);
		free(data->img);
		free(data);
		exit_error("Error: Fails to open window");
	}
	data->img->mlx_img = mlx_new_image(data->mlx_ptr, W_WIDTH, W_HEIGHT);
	data->win_ptr = mlx_new_window(data->mlx_ptr,
			W_WIDTH, W_HEIGHT, "Natalie's window");
	if (!(data->win_ptr) || !(data->img->mlx_img))
	{
		close_window(data);
		exit_error("Error: Fails to create window.");
	}
	data->img->addr = mlx_get_data_addr(data->img->mlx_img,
			&data->img->bpp, &data->img->line_len, &data->img->endian);
}

int	close_window(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img->mlx_img);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	if (data->img)
		free(data->img);
	free_mem(data->map);
	free(data->mlx_ptr);
	free(data);
	ft_printf("%sWindow is closed. Bye !! %s\n", YELLOW, YELLOW);
	ft_printf("%s", RESET_COLOR);
	exit(0);
	return (0);
}
