NAME    		= cub3D
CC      		= cc
CFLAGS  		= -Wall -Wextra -Werror -g3
LIBFT			= ./libft/libft.a
INC				= -I$(LIBFT_HDR_DIR) -I$(HDR_DIR)
HDR_DIR			= inc
LIBFT_HDR_DIR	= libft/include

LIBFLAGS 		= -lm
MLXFLAGS 		= -I/usr/include -Imlx
LINKFLAGS 		= -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11

MLX_DIR			= mlx/
MLX_HDR			= mlx.h
MLX_REPO		= https://github.com/42paris/minilibx-linux.git

GREEN			= \033[1;32m
RESET			= \033[0m
RED				= \033[0;31m
BLUE			= \033[34m
YELLOW			= \033[0;33m


############################# SOURCES #############################

SRCS_DIR 		= src/
SRCS    	=	$(SRCS_DIR)main.c \
				$(SRCS_DIR)check_map.c \
				$(SRCS_DIR)colors.c \
				$(SRCS_DIR)controls.c \
				$(SRCS_DIR)crosshair.c \
				$(SRCS_DIR)draw_utils.c \
				$(SRCS_DIR)draw.c \
				$(SRCS_DIR)errors.c \
				$(SRCS_DIR)file.c \
 				$(SRCS_DIR)garbage_collector.c \
				$(SRCS_DIR)init.c \
				$(SRCS_DIR)load_walls.c \
				$(SRCS_DIR)map.c \
				$(SRCS_DIR)mouse.c \
				$(SRCS_DIR)move.c \
				$(SRCS_DIR)parse.c \
				$(SRCS_DIR)raycasting.c \
				$(SRCS_DIR)render.c \
				$(SRCS_DIR)textures.c \
				$(SRCS_DIR)trim.c

# $(SRCS_DIR).main_deprecated.c OLD MAIN FILE FOR PARSING ONLY
# $(SRCS_DIR).init.deprecated.c

############################# SOURCES BONUS #############################


SRCS_BONUS_DIR 	= src_bonus/
SRCS_BONUS    = $(SRCS_BONUS_DIR)main.c \
				$(SRCS_BONUS_DIR)check_map.c \
				$(SRCS_BONUS_DIR)colors.c \
				$(SRCS_BONUS_DIR)controls.c \
				$(SRCS_BONUS_DIR)crosshair.c \
				$(SRCS_BONUS_DIR)draw_utils.c \
				$(SRCS_BONUS_DIR)draw.c \
				$(SRCS_BONUS_DIR)errors.c \
				$(SRCS_BONUS_DIR)file.c \
 				$(SRCS_BONUS_DIR)garbage_collector.c \
				$(SRCS_BONUS_DIR)init.c \
				$(SRCS_BONUS_DIR)load_walls.c \
				$(SRCS_BONUS_DIR)map.c \
				$(SRCS_BONUS_DIR)mouse.c \
				$(SRCS_BONUS_DIR)move.c \
				$(SRCS_BONUS_DIR)parse.c \
				$(SRCS_BONUS_DIR)raycasting.c \
				$(SRCS_BONUS_DIR)render.c \
				$(SRCS_BONUS_DIR)textures.c \
				$(SRCS_BONUS_DIR)trim.c \
				$(SRCS_BONUS_DIR)pickaxe.c \
				$(SRCS_BONUS_DIR)totem.c \
				$(SRCS_BONUS_DIR)doors.c

############################# DIRECTORIES ##############################

OBJS_DIR = .objs/
OBJS    = $(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)
DEPS := $(OBJS:.o=.d)

OBJS_BONUS_DIR    = .objs_bonus/
OBJS_BONUS        = $(SRCS_BONUS:$(SRCS_BONUS_DIR)%.c=$(OBJS_BONUS_DIR)%.o)
DEPS_BONUS        := $(OBJS_BONUS:.o=.d)

############################# RULES ##############################

all: $(LIBFT) $(NAME)

$(LIBFT):	force $(LIBFT_HDR_DIR)
	@make --no-print-directory -C ./libft

mlx:
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "Cloning MiniLibX..."; \
		git clone $(MLX_REPO) $(MLX_DIR) && cd $(MLX_DIR) && ./configure && make; \
	else \
		echo "MiniLibX already present."; \
fi

force:
$(NAME):	mlx $(OBJS) libft/libft.a
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LINKFLAGS) $(LIBFLAGS) -o $(NAME) 
	@echo "$(GREEN)Compilation successful! 🎉$(RESET)"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c 
	@mkdir -p  $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -MMD -c $< -o $@ $(MLXFLAGS)
	@echo "$(BLUE)Compiling : $< 🔧$(RESET)"

bonus: $(LIBFT) mlx $(OBJS_BONUS)
	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT) $(LINKFLAGS) $(LIBFLAGS) -o cub3D_bonus
	@echo "$(YELLOW)Bonus compilation successful! ✨$(RESET)"

$(OBJS_BONUS_DIR)%.o: $(SRCS_BONUS_DIR)%.c
	@mkdir -p  $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -MMD -c $< -o $@ $(MLXFLAGS)
	@echo "$(BLUE)Compiling bonus : $< 🚀$(RESET)"

clean:
	@make --no-print-directory clean -C libft
	@rm -rf $(OBJS_DIR)
	@rm -rf $(OBJS_BONUS_DIR)
	@echo "$(RED)Cleaned project 🗑️$(RESET)"

fclean:
	@make --no-print-directory fclean -C libft
	@rm -rf $(NAME) && rm -rf $(OBJS_DIR)
	@rm -rf cub3D_bonus && rm -rf $(OBJS_BONUS_DIR)
	@rm -rf mlx/
	@echo "$(RED)Fully cleaned project 🗑️$(RESET)"
	@echo "$(RED)Removed mlx$(RESET)"

re: fclean all

-include $(DEPS)
-include $(DEPS_BONUS)

.PHONY: all clean fclean re bonus mlx 
