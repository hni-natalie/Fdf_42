/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:17:18 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/12/21 11:52:19 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define W_WIDTH 1600
# define W_HEIGHT 800
# define MLX_ERROR 1

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"

# include <X11/keysym.h>
# include <X11/X.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

// color in ANSI escape code 
# define RED "\033[31m"
# define YELLOW "\033[33m"

// color in hexa code
# define WHITE 0xffffff
# define PURPLE 0x6500ff

# define M_PINK 0xf3dbfe
# define M_PURPLE 0x9851e7
# define BROWN 0xecddcd

// adjustment
# define ZOOM 0.1
# define TRANS 2.5
# define ROT 0.01
# define FLATTEN 0.05

// reset code which change the text color to the default terminal setting
# define RESET_COLOR "\033[0m"

# define HEXA_BASE "0123456789ABCDEF"

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
} t_point;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
} t_img;

typedef struct s_map
{
	int	rows;
	int	columns;
	int	**height;
	int	**color;
	int	min_height;
	int	max_height;
	int	got_color;
} t_map;

typedef	struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	*img;
	t_map	*map;
	int		shift_x;
	int		shift_y;
	float	rot_x;
	float	rot_y;
	float	rot_z;
	float	zoom;
	int		isometric;
	float	flatten;
	int		change_color;
} t_data;


// main
t_map	*handle_map(char *file);
void	execute_mlx(t_map *map);
int		handle_keypress(int keycode, t_data *data);
void	control_menu(t_data *data);

// handle map
void	find_area(int fd, t_map *map);
void	find_width(char *line, char **x_axis, t_map *map);
void	get_height_color(int fd, t_map *map);
int		min_max_z(int z, t_map *map);
int		convert_hex_color(char *color, t_map *map);

// handle mlx
void	init_mlx(t_data *data);
t_data	*init_data(t_map *map);
void	set_default(t_data *data);
int		ft_greater(int x, int y);
int		close_window(t_data *data);

// bresenham algorithm
void	draw_map(t_data *data);
void	bresenham(t_data *data, t_point start, t_point end);
void	init_bresenham(t_point start, t_point end, t_point *delta, t_point *sign);
t_point	new_point(int x, int y, t_data *data);
void	put_pixel(t_data *data, int x, int y, int color);

// adjustment
void	zoom_in_out(int keycode, t_data *data);
void	adjust_alt(int keycode, t_data *data);
void	rotation(int keycode, t_data *data);
void	translation(int keycode, t_data *data);

// transformation
t_point	transform(t_data *data, t_point point);
void	rot_x_y_z(t_data *data, int *x, int *y, int *z);
void	isometric(t_data *data, int *x, int *y, int z);

// color
int		cal_color(t_data *data, int height);
float	color_percentage(int min, int max, int current);
int		get_color(t_point start, t_point end, t_point delta);
int		partial_color(int start, int end, float percent);

// utils
void	ft_calloc_arr(t_map *map);
void	exit_error(char *msg);
void	free_arr(char	**z_cor);
void	free_mem(t_map *map);
int		ft_atoi_base(char *color, char *base);

#endif