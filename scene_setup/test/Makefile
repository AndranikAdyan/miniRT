# **************************************************************************** #
#                              scene_setup/Makefile                           #
# **************************************************************************** #

NAME		= scene_test

# Компилятор и флаги
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g

# --- Файлы ---
SRC_FILES	= ../config_utils.c ../scene_loader.c ../validation.c ../types_config.c test.c
GNL_FILE	= ../../library/get_next_line/get_next_line.c
LIBFT_DIR	= ../../library/libft
LIBFT		= $(LIBFT_DIR)/libft.a

# --- Пути к исходникам ---
SRCS		= $(addprefix ./, $(SRC_FILES)) $(GNL_FILE)

# --- Инклуды ---
INCLUDES	= -I. -I../  -I../../library/libft -I../../library/get_next_line

# --- Цель по умолчанию ---
all: $(NAME)

# --- Сборка libft, если нужно ---
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# --- Сборка теста ---
$(NAME): $(SRCS) $(LIBFT)
	$(CC) $(CFLAGS) $(SRCS) $(LIBFT) -o $(NAME) -lm $(INCLUDES)

# --- Очистка ---
clean:
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

