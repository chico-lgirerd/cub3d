# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tiaperei <tiaperei@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/05 17:00:03 by lgirerd           #+#    #+#              #
#    Updated: 2025/09/30 12:54:38 by tiaperei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    		= cub3D
CC      		= cc
CFLAGS  		= -Wall -Wextra -Werror
HDR_DIR			= include
LIBFT_DIR		= libft
MLX_DIR			= minilibx-linux

INC				= -I$(HDR_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)
LIBFT 			= $(LIBFT_DIR)/libft.a
MLX 			= $(MLX_DIR)/libmlx.a
MLX_LIB 		= -L$(MLX_DIR) -lmlx -lX11 -lXext
MLX_REPO 		= https://github.com/42paris/minilibx-linux.git

############################# SOURCES #############################

SRCS_DIR 	= srcs/
SRCS    	= $(SRCS_DIR)main.c \

############################# OBJECTS/DEPENDANCES ##############################

OBJS_DIR = .objs/
OBJS = $(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)
DEPS = $(OBJS:.o=.d)

############################# RULES ##############################

all: $(LIBFT) $(MLX) $(NAME)

$(MLX_DIR):
	git clone $(MLX_REPO) $(MLX_DIR)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX): $(MLX_DIR)
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_LIB) -o $(NAME)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HDR_DIR)
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INC) -MMD -c $< -o $@
	
clean:
	rm -rf $(OBJS_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean:
	rm -rf $(NAME) && rm -rf $(OBJS_DIR) && rm -rf $(MLX_DIR)
	$(MAKE) -C $(LIBFT_DIR) fclean
	
re: fclean all

norm: 
	@norminette srcs || true
	@norminette include || true
	@norminette libft | grep error || true

-include $(DEPS)

.PHONY: all clean fclean re
