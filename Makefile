NAME := pipex
NAMEB := pipex_bonus
SRCFILES := pipex.c pipex_utils.c pipex_children.c pipex_cmds.c pipex_paths.c pipex_cleanup.c
SRCFILESB := pipex_bonus.c pipex_utils_bonus.c pipex_children_bonus.c pipex_cmds_bonus.c pipex_paths_bonus.c pipex_cleanup_bonus.c
OBJS := $(SRCFILES:.c=.o)
OBJSB := $(SRCFILESB:.c=.o)
INCLUDES := pipex.h
INCLUDESB := pipex_bonus.h
CC := gcc
CFLAGS := -Wall -Wextra -Werror -g3
LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(INCLUDES)
	@echo "Building $(NAME)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(NAMEB): $(LIBFT) $(OBJSB) $(INCLUDESB)
	@echo "Building $(NAMEB)"
	@$(CC) $(CFLAGS) $(OBJSB) $(LIBFT) -o $(NAMEB)

%.o: %.c
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@echo "Building $(LIBFT)"
	@$(MAKE) -C $(LIBFT_DIR)

bonus: $(LIBFT) $(NAMEB)

clean:
	@echo "Removing object files"
	@rm -f $(OBJS) $(OBJSB)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@echo "Removing object files and $(NAME) or $(NAMEB)"
	@rm -f $(NAME) $(NAMEB)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re
