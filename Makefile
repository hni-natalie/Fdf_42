# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hni-xuan <hni-xuan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/10 09:26:38 by hni-xuan          #+#    #+#              #
#    Updated: 2024/12/21 10:52:01 by hni-xuan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRCS_DIR = srcs
OBJS_DIR = objs
LIBFT_DIR = ./libft

MLX_DIR = ./minilibx-linux
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lm -lX11 -lXext

SRCS_FILES = main utils handle_map handle_mlx color bresenham_algo \
				adjustment transformation 

SRCS = $(addprefix $(SRCS_DIR)/, $(addsuffix .c, $(SRCS_FILES)))
OBJS = $(addprefix $(OBJS_DIR)/, $(addsuffix .o, $(SRCS_FILES)))

NAME = fdf

all : $(NAME)

# Compiles and links all the object files, applies the compiler flags links against the libft.a and MiniLibX libraries 
$(NAME): $(LIBFT_DIR)/libft.a $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(MLX_FLAGS) -L$(LIBFT_DIR) -lft

$(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -Iinclude -I$(MLX_DIR) -I$(LIBFT_DIR) -c $< -o $@ 

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(LIBFT_DIR)/libft.a:
	make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -rf $(OBJS_DIR)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
