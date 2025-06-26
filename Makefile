MAKEFLAGS += --no-print-directory -s

RED     = \e[31m
GREEN   = \e[32m
YELLOW  = \e[33m
CYAN    = \e[36m
RESET   = \e[0m

NAME = miniRT

LIBFT_DIR = libs/libft
MLX_DIR   = libs/minilibx-linux

LIBFT = -L$(LIBFT_DIR) -lft
MLX   = -L$(MLX_DIR) -lmlx -lm -lX11 -lXext

SRC := $(shell find . -path "./$(LIBFT_DIR)" -prune -o -path "./$(MLX_DIR)" -prune -o -name "*.c" ! -name "test.c" -print)

INCLUDES := $(shell find . -name "*.h" -exec dirname {} \; | sed 's/^/-I/')

HEADERS := $(shell find . -path './libs/minilibx-linux' -prune -o -name "*.h" -print)

BUILD_DIR = build
OBJ := $(patsubst ./%.c,$(BUILD_DIR)/%.o,$(SRC))

CC = cc
FLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=address

all: build configure lib $(NAME)

$(NAME): $(OBJ) $(LIBFT_DIR)/libft.a $(MLX_DIR)/libmlx.a
	@$(CC) $(FLAGS) $(INCLUDES) $(OBJ) -o $(NAME) $(LIBFT) $(MLX)
	@echo "${YELLOW}MiniRT Done!${RESET}\n"

$(BUILD_DIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@
	@echo "  ✅ ${GREEN}$<${RESET}"

build:
	@mkdir -p $(BUILD_DIR)

lib:
	@make -C $(LIBFT_DIR)

configure:
	@make -C $(MLX_DIR) > /dev/null

mlxclean:
	@echo "🗑  ${RED}Minilibx Cleaning...${RESET}"
	@make -C $(MLX_DIR) clean > /dev/null

clean:
	@echo "🗑  ${RED}Remove Object Files...${RESET}"
	@rm -rf $(BUILD_DIR)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "🗑  ${RED}Remove Executable Files...${RESET}"

norm:
	@norminette $(SRC) libs/libft

re: fclean mlxclean all

.PHONY: all lib configure mlxclean build clean fclean re
