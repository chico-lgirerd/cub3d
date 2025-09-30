NAME    		= cub3D
CC      		= cc
CFLAGS  		= -Wall -Wextra -Werror
LIBFT			= ./libft/libft.a
INC				= -I$(LIBFT_HDR_DIR) -I$(HDR_DIR)
HDR_DIR			= include
LIBFT_HDR_DIR	= libft/include
GREEN			= \033[1;32m
RESET			= \033[0m
RED				= \033[0;31m
BLUE			= \033[34m
YELLOW			= \033[0;33m


############################# SOURCES #############################

SRCS_DIR 		= src/
PARSING_DIR 	= src/parsing/
SRCS    	=

############################# DIRECTORIES ##############################

OBJS_DIR = .objs/
OBJS    = $(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)
DEPS := $(OBJS:.o=.d)

############################# RULES ##############################

all: $(LIBFT) $(NAME)

$(LIBFT): force $(LIBFT_HDR_DIR)
	@make --no-print-directory -C ./libft

force:
$(NAME): $(OBJS) libft/libft.a
	@$(CC) $(CFLAGS) -lreadline $(OBJS) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)Compilation successful! 🎉$(RESET)"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HDR_DIR)
	@mkdir -p  $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/parsing
	@mkdir -p $(OBJS_DIR)/builtins
	@mkdir -p $(OBJS_DIR)/utils
	@mkdir -p $(OBJS_DIR)/exec
	@$(CC) $(CFLAGS) $(INC) -MMD -c $< -o $@
	@echo "$(BLUE)Compiling : $< 🔧$(RESET)"

clean:
	@make --no-print-directory clean -C libft
	@rm -rf $(OBJS_DIR)
	@echo "$(RED)Cleaned project 🗑️$(RESET)"

fclean:
	@make --no-print-directory fclean -C libft
	@rm -rf $(NAME) && rm -rf $(OBJS_DIR)
	@echo "$(RED)Fully cleaned project 🗑️$(RESET)"
	
re: fclean all

norm:
	@norminette srcs || true
	@norminette include || true
	@norminette libft | grep Error || true 

val: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
	--show-mismatched-frees=yes --trace-children=yes \
	--suppressions=rl_leaks.supp --track-fds=yes --quiet ./$(NAME)

-include $(DEPS)

.PHONY: all clean fclean re
