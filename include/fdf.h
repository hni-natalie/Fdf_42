/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:17:18 by hni-xuan          #+#    #+#             */
/*   Updated: 2024/12/13 15:51:30 by hni-xuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WINDOW_WIDTH 600
# define WINDOW_HEIGHT 300
# define MLX_ERROR 1

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"

# include <X11/keysym.h>
# include <X11/X.h>
# include <stdlib.h>
# include <stdio.h>

// yellow color in ANSI escape code 
# define YELLOW "\033[31m"
// reset code which change the text color to the default terminal setting
# define RESET_COLOR "\033[0m"

# define WHITE 0xFFFFFF

# define HEXA_BASE "0123456789ABCDEF"

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
} t_img;

typedef	struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
} t_data;

typedef struct s_map
{
	int	rows;
	int	columns;
	int	**height;
	int	**color;
	int	min_height;
	int	max_height;
} t_map;

void	img_pix_put(t_img *img, int x, int y, int color);
t_map	*handle_map(char *file);
void	find_area(int fd, t_map *map);
void	get_height_color(int fd, t_map *map);
int		min_max_z(int z, t_map *map);
int		convert_hex_color(char *color);

// utils
void	ft_calloc_arr(t_map *map);
void	exit_error(char *msg);
void	free_arr(char	**z_cor);
void	free_mem(t_map *map);
int		ft_atoi_base(char *color, char *base);

#endif