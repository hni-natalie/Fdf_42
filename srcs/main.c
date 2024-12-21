/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:05:46 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/12/21 11:52:48 by hni-xuan         ###   ########.fr       */
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
	execute_mlx(map);
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

void	execute_mlx(t_map *map)
{
	t_data	*data;

	data = init_data(map);
	init_mlx(data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &handle_keypress, data);
	mlx_hook(data->win_ptr, DestroyNotify, 0, &close_window, data);
	draw_map(data);
	mlx_loop(data->mlx_ptr);
}

int	handle_keypress(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		close_window(data);
	else if (keycode == XK_BackSpace)
		set_default(data);
	else if (keycode == XK_Tab)
		data->isometric = !(data->isometric);
	else if (keycode == XK_Shift_R || keycode == XK_Return)
		zoom_in_out(keycode, data);
	else if (keycode == XK_space)
		data->change_color = !(data->change_color);
	else if (keycode == XK_9 || keycode == XK_0)
		adjust_alt(keycode, data);
	else if (keycode == XK_1 || keycode == XK_2 || keycode == XK_3
		|| keycode == XK_4 || keycode == XK_5 || keycode == XK_6)
		rotation(keycode, data);
	else if (keycode == XK_Up || keycode == XK_Down || keycode == XK_Left
		|| keycode == XK_Right)
		translation(keycode, data);
	draw_map(data);
	return (0);
}

void	control_menu(t_data *data)
{
	void	*mlx;
	void	*win;
	int		vp;

	mlx = data->mlx_ptr;
	win = data->win_ptr;
	vp = 20;
	mlx_string_put(mlx, win, 30, vp += 30, WHITE, "CONTROLS:");
	mlx_string_put(mlx, win, 50, vp += 20, BROWN, "BackSpace: RESET");
	mlx_string_put(mlx, win, 50, vp += 20, BROWN, "Space: CHANGE COLOR");
	mlx_string_put(mlx, win, 50, vp += 20, BROWN, "'Enter': ZOOM IN");
	mlx_string_put(mlx, win, 50, vp += 20, BROWN, "'Right Shift': ZOOM OUT");
	mlx_string_put(mlx, win, 50, vp += 20, BROWN, "'9'/'0': FLATTEN");
	mlx_string_put(mlx, win, 50, vp += 20, BROWN, "'Up': MOVE UP");
	mlx_string_put(mlx, win, 50, vp += 20, BROWN, "'Down': MOVE DOWN");
	mlx_string_put(mlx, win, 50, vp += 20, BROWN, "'Left': MOVE LEFT");
	mlx_string_put(mlx, win, 50, vp += 20, BROWN, "'Right': MOVE RIGHT");
	mlx_string_put(mlx, win, 30, vp += 30, WHITE, "ROTATE:");
	mlx_string_put(mlx, win, 50, vp += 20, BROWN, "'1'/'2': X-AXIS");
	mlx_string_put(mlx, win, 50, vp += 20, BROWN, "'3'/'4': Y-AXIS");
	mlx_string_put(mlx, win, 50, vp += 20, BROWN, "'5'/'6': Z-AXIS");
	mlx_string_put(mlx, win, 30, vp += 30, WHITE, "TOGGLE:");
	mlx_string_put(mlx, win, 50, vp += 20, BROWN, "'TAB': ISOMETRIC/PARALLEL");
	mlx_string_put(mlx, win, 30, vp += 30, WHITE, "EXIT:");
	mlx_string_put(mlx, win, 50, vp += 20, BROWN, "'ESC'/'(x)': CLOSE");
}
